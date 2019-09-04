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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ MTU_CR (int) ; 
 unsigned long MTU_CRn_32BITS ; 
 unsigned long MTU_CRn_ENA ; 
 unsigned long MTU_CRn_ONESHOT ; 
 scalar_t__ MTU_IMSC ; 
 scalar_t__ MTU_LR (int) ; 
 unsigned long clk_prescale ; 
 scalar_t__ mtu_base ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int nmdk_clkevt_next(unsigned long evt, struct clock_event_device *ev)
{
	writel(1 << 1, mtu_base + MTU_IMSC);
	writel(evt, mtu_base + MTU_LR(1));
	/* Load highest value, enable device, enable interrupts */
	writel(MTU_CRn_ONESHOT | clk_prescale |
	       MTU_CRn_32BITS | MTU_CRn_ENA,
	       mtu_base + MTU_CR(1));

	return 0;
}