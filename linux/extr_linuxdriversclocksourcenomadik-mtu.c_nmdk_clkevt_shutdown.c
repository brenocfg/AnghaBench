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
 scalar_t__ MTU_IMSC ; 
 scalar_t__ MTU_LR (int) ; 
 scalar_t__ mtu_base ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int nmdk_clkevt_shutdown(struct clock_event_device *evt)
{
	writel(0, mtu_base + MTU_IMSC);
	/* disable timer */
	writel(0, mtu_base + MTU_CR(1));
	/* load some high default value */
	writel(0xffffffff, mtu_base + MTU_LR(1));
	return 0;
}