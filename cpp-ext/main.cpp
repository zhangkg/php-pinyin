#include <phpcpp.h>
#include "master.h"

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {

    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module()
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("php-pinyin", "1.0");

        // we have to class - master
        Php::Class<Master> master("pinyin");

        master.method<&Master::__construct>("__construct", {
            Php::ByVal("dictPath", Php::Type::String, false),
            Php::ByVal("withTone", Php::Type::Bool, false)
          });

        master.method<&Master::convert>("convert", {
            Php::ByVal("words", Php::Type::String),
            Php::ByVal("tone", Php::Type::Bool, false),
          });

        master.method<&Master::generateDict>("generateDict", {
            Php::ByVal("string", Php::Type::String)
          });

        extension.add(Php::Ini("pinyin.dict_path", "~/var/data/libpinyin/dict/"));
        extension.add(Php::Ini("pinyin.dict_tone", 0));

        // add all classes to the extension
        extension.add(master);

        extension.onStartup([]() {
          });

        extension.onShutdown([]() {
          });

        extension.onRequest([]() {
          });

        extension.onIdle([]() {
          });


        // return the extension
        return extension;
    }
}