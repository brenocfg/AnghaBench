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
 int /*<<< orphan*/  INTC_IDLE ; 
 int /*<<< orphan*/  INTC_IDLE_TURBO ; 
 int /*<<< orphan*/  INTC_SYSCONFIG ; 
 int /*<<< orphan*/  intc_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void omap3_intc_prepare_idle(void)
{
	/*
	 * Disable autoidle as it can stall interrupt controller,
	 * cf. errata ID i540 for 3430 (all revisions up to 3.1.x)
	 */
	intc_writel(INTC_SYSCONFIG, 0);
	intc_writel(INTC_IDLE, INTC_IDLE_TURBO);
}