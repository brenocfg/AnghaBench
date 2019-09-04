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
 scalar_t__ TWD_TIMER_INTSTAT ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ twd_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int twd_timer_ack(void)
{
	if (readl_relaxed(twd_base + TWD_TIMER_INTSTAT)) {
		writel_relaxed(1, twd_base + TWD_TIMER_INTSTAT);
		return 1;
	}

	return 0;
}