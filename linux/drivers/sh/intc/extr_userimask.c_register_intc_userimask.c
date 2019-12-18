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

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  SZ_4K ; 
 scalar_t__ intc_get_dfl_prio_level () ; 
 int ioremap_nocache (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 int uimask ; 
 scalar_t__ unlikely (int) ; 

int register_intc_userimask(unsigned long addr)
{
	if (unlikely(uimask))
		return -EBUSY;

	uimask = ioremap_nocache(addr, SZ_4K);
	if (unlikely(!uimask))
		return -ENOMEM;

	pr_info("userimask support registered for levels 0 -> %d\n",
		intc_get_dfl_prio_level() - 1);

	return 0;
}