#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sh_type; int sh_size; } ;
struct section {TYPE_2__* link; TYPE_3__* symtab; TYPE_1__ shdr; } ;
struct TYPE_9__ {int e_shnum; } ;
struct TYPE_8__ {int st_name; } ;
struct TYPE_7__ {char* strtab; } ;
typedef  TYPE_3__ Elf_Sym ;

/* Variables and functions */
 scalar_t__ SHT_SYMTAB ; 
 TYPE_5__ ehdr ; 
 struct section* secs ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static Elf_Sym *sym_lookup(const char *symname)
{
	int i;
	for (i = 0; i < ehdr.e_shnum; i++) {
		struct section *sec = &secs[i];
		long nsyms;
		char *strtab;
		Elf_Sym *symtab;
		Elf_Sym *sym;

		if (sec->shdr.sh_type != SHT_SYMTAB)
			continue;

		nsyms = sec->shdr.sh_size/sizeof(Elf_Sym);
		symtab = sec->symtab;
		strtab = sec->link->strtab;

		for (sym = symtab; --nsyms >= 0; sym++) {
			if (!sym->st_name)
				continue;
			if (strcmp(symname, strtab + sym->st_name) == 0)
				return sym;
		}
	}
	return 0;
}