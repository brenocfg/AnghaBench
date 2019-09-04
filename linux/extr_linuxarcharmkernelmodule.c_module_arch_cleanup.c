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

/* Variables and functions */

void
module_arch_cleanup(struct module *mod)
{
#ifdef CONFIG_ARM_UNWIND
	int i;

	for (i = 0; i < ARM_SEC_MAX; i++)
		if (mod->arch.unwind[i])
			unwind_table_del(mod->arch.unwind[i]);
#endif
}