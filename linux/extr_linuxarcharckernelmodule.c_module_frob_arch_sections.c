#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* secstr; } ;
struct module {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  Elf_Shdr ;
typedef  int /*<<< orphan*/  Elf_Ehdr ;

/* Variables and functions */

int module_frob_arch_sections(Elf_Ehdr *hdr, Elf_Shdr *sechdrs,
			      char *secstr, struct module *mod)
{
#ifdef CONFIG_ARC_DW2_UNWIND
	mod->arch.unw_sec_idx = 0;
	mod->arch.unw_info = NULL;
#endif
	mod->arch.secstr = secstr;
	return 0;
}