#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct ppc_plt_entry {int* jump; } ;
struct TYPE_6__ {size_t core_plt_section; size_t init_plt_section; } ;
struct TYPE_5__ {void* base; int size; } ;
struct module {TYPE_2__ arch; TYPE_1__ core_layout; } ;
struct TYPE_7__ {scalar_t__ sh_addr; } ;
typedef  TYPE_3__ Elf32_Shdr ;
typedef  int Elf32_Addr ;

/* Variables and functions */
 scalar_t__ entry_matches (struct ppc_plt_entry*,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,...) ; 

__attribute__((used)) static uint32_t do_plt_call(void *location,
			    Elf32_Addr val,
			    const Elf32_Shdr *sechdrs,
			    struct module *mod)
{
	struct ppc_plt_entry *entry;

	pr_debug("Doing plt for call to 0x%x at 0x%x\n", val, (unsigned int)location);
	/* Init, or core PLT? */
	if (location >= mod->core_layout.base
	    && location < mod->core_layout.base + mod->core_layout.size)
		entry = (void *)sechdrs[mod->arch.core_plt_section].sh_addr;
	else
		entry = (void *)sechdrs[mod->arch.init_plt_section].sh_addr;

	/* Find this entry, or if that fails, the next avail. entry */
	while (entry->jump[0]) {
		if (entry_matches(entry, val)) return (uint32_t)entry;
		entry++;
	}

	entry->jump[0] = 0x3d800000+((val+0x8000)>>16); /* lis r12,sym@ha */
	entry->jump[1] = 0x398c0000 + (val&0xffff);     /* addi r12,r12,sym@l*/
	entry->jump[2] = 0x7d8903a6;                    /* mtctr r12 */
	entry->jump[3] = 0x4e800420;			/* bctr */

	pr_debug("Initialized plt for 0x%x at %p\n", val, entry);
	return (uint32_t)entry;
}