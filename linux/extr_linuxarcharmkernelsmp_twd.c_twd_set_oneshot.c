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
 scalar_t__ TWD_TIMER_CONTROL ; 
 int TWD_TIMER_CONTROL_IT_ENABLE ; 
 int TWD_TIMER_CONTROL_ONESHOT ; 
 scalar_t__ twd_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int twd_set_oneshot(struct clock_event_device *clk)
{
	/* period set, and timer enabled in 'next_event' hook */
	writel_relaxed(TWD_TIMER_CONTROL_IT_ENABLE | TWD_TIMER_CONTROL_ONESHOT,
		       twd_base + TWD_TIMER_CONTROL);
	return 0;
}