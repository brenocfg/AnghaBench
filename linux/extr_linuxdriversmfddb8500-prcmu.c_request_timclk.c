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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  PRCM_TCR ; 
 int PRCM_TCR_DOZE_MODE ; 
 int PRCM_TCR_STOP_TIMERS ; 
 int PRCM_TCR_TENSEL_MASK ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int request_timclk(bool enable)
{
	u32 val = (PRCM_TCR_DOZE_MODE | PRCM_TCR_TENSEL_MASK);

	if (!enable)
		val |= PRCM_TCR_STOP_TIMERS;
	writel(val, PRCM_TCR);

	return 0;
}