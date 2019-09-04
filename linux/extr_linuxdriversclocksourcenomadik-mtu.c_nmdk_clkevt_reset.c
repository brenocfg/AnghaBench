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
 scalar_t__ MTU_BGLR (int) ; 
 scalar_t__ MTU_CR (int) ; 
 int MTU_CRn_32BITS ; 
 int MTU_CRn_ENA ; 
 int MTU_CRn_PERIODIC ; 
 scalar_t__ MTU_IMSC ; 
 scalar_t__ MTU_LR (int) ; 
 int clk_prescale ; 
 scalar_t__ clkevt_periodic ; 
 scalar_t__ mtu_base ; 
 int /*<<< orphan*/  nmdk_clkevt_next (int,int /*<<< orphan*/ *) ; 
 int nmdk_cycle ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void nmdk_clkevt_reset(void)
{
	if (clkevt_periodic) {
		/* Timer: configure load and background-load, and fire it up */
		writel(nmdk_cycle, mtu_base + MTU_LR(1));
		writel(nmdk_cycle, mtu_base + MTU_BGLR(1));

		writel(MTU_CRn_PERIODIC | clk_prescale |
		       MTU_CRn_32BITS | MTU_CRn_ENA,
		       mtu_base + MTU_CR(1));
		writel(1 << 1, mtu_base + MTU_IMSC);
	} else {
		/* Generate an interrupt to start the clockevent again */
		(void) nmdk_clkevt_next(nmdk_cycle, NULL);
	}
}