#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int init_plt_section; unsigned int core_plt_section; } ;
struct module {TYPE_1__ arch; } ;
struct TYPE_10__ {unsigned int e_shnum; } ;
struct TYPE_9__ {int sh_name; void* sh_size; } ;
typedef  TYPE_2__ Elf32_Shdr ;
typedef  TYPE_3__ Elf32_Ehdr ;

/* Variables and functions */
 int ENOEXEC ; 
 void* get_plt_size (TYPE_3__*,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

int module_frob_arch_sections(Elf32_Ehdr *hdr,
			      Elf32_Shdr *sechdrs,
			      char *secstrings,
			      struct module *me)
{
	unsigned int i;

	/* Find .plt and .init.plt sections */
	for (i = 0; i < hdr->e_shnum; i++) {
		if (strcmp(secstrings + sechdrs[i].sh_name, ".init.plt") == 0)
			me->arch.init_plt_section = i;
		else if (strcmp(secstrings + sechdrs[i].sh_name, ".plt") == 0)
			me->arch.core_plt_section = i;
	}
	if (!me->arch.core_plt_section || !me->arch.init_plt_section) {
		pr_err("Module doesn't contain .plt or .init.plt sections.\n");
		return -ENOEXEC;
	}

	/* Override their sizes */
	sechdrs[me->arch.core_plt_section].sh_size
		= get_plt_size(hdr, sechdrs, secstrings, 0);
	sechdrs[me->arch.init_plt_section].sh_size
		= get_plt_size(hdr, sechdrs, secstrings, 1);
	return 0;
}