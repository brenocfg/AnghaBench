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
 unsigned long DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ TWD_TIMER_CONTROL ; 
 unsigned long TWD_TIMER_CONTROL_ENABLE ; 
 unsigned long TWD_TIMER_CONTROL_IT_ENABLE ; 
 unsigned long TWD_TIMER_CONTROL_PERIODIC ; 
 scalar_t__ TWD_TIMER_LOAD ; 
 scalar_t__ twd_base ; 
 int /*<<< orphan*/  twd_timer_rate ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,scalar_t__) ; 

__attribute__((used)) static int twd_set_periodic(struct clock_event_device *clk)
{
	unsigned long ctrl = TWD_TIMER_CONTROL_ENABLE |
			     TWD_TIMER_CONTROL_IT_ENABLE |
			     TWD_TIMER_CONTROL_PERIODIC;

	writel_relaxed(DIV_ROUND_CLOSEST(twd_timer_rate, HZ),
		       twd_base + TWD_TIMER_LOAD);
	writel_relaxed(ctrl, twd_base + TWD_TIMER_CONTROL);
	return 0;
}