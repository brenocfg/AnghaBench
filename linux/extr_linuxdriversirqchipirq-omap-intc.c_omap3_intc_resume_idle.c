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
 int /*<<< orphan*/  INTC_SYSCONFIG ; 
 int /*<<< orphan*/  intc_writel (int /*<<< orphan*/ ,int) ; 

void omap3_intc_resume_idle(void)
{
	/* Re-enable autoidle */
	intc_writel(INTC_SYSCONFIG, 1);
	intc_writel(INTC_IDLE, 0);
}