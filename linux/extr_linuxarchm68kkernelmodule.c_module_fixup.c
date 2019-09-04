#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct module {int dummy; } ;
struct m68k_fixup_info {int dummy; } ;

/* Variables and functions */

void module_fixup(struct module *mod, struct m68k_fixup_info *start,
		  struct m68k_fixup_info *end)
{
#ifdef CONFIG_MMU
	struct m68k_fixup_info *fixup;

	for (fixup = start; fixup < end; fixup++) {
		switch (fixup->type) {
		case m68k_fixup_memoffset:
			*(u32 *)fixup->addr = m68k_memoffset;
			break;
		case m68k_fixup_vnode_shift:
			*(u16 *)fixup->addr += m68k_virt_to_node_shift;
			break;
		}
	}
#endif
}