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
 scalar_t__ HW_TIMROT_FIXED_COUNTn (int) ; 
 scalar_t__ HW_TIMROT_TIMCOUNTn (int) ; 
 int /*<<< orphan*/  __raw_writel (int,scalar_t__) ; 
 scalar_t__ mxs_timrot_base ; 
 int /*<<< orphan*/  timrot_irq_acknowledge () ; 
 int /*<<< orphan*/  timrot_irq_disable () ; 
 scalar_t__ timrot_is_v1 () ; 

__attribute__((used)) static void mxs_irq_clear(char *state)
{
	/* Disable interrupt in timer module */
	timrot_irq_disable();

	/* Set event time into the furthest future */
	if (timrot_is_v1())
		__raw_writel(0xffff, mxs_timrot_base + HW_TIMROT_TIMCOUNTn(1));
	else
		__raw_writel(0xffffffff,
			     mxs_timrot_base + HW_TIMROT_FIXED_COUNTn(1));

	/* Clear pending interrupt */
	timrot_irq_acknowledge();

#ifdef DEBUG
	pr_info("%s: changing mode to %s\n", __func__, state)
#endif /* DEBUG */
}