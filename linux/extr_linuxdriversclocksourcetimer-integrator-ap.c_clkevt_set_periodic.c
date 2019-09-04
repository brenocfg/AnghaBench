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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TIMER_CTRL ; 
 int TIMER_CTRL_ENABLE ; 
 int TIMER_CTRL_PERIODIC ; 
 scalar_t__ TIMER_LOAD ; 
 scalar_t__ clkevt_base ; 
 int readl (scalar_t__) ; 
 int timer_reload ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int clkevt_set_periodic(struct clock_event_device *evt)
{
	u32 ctrl = readl(clkevt_base + TIMER_CTRL) & ~TIMER_CTRL_ENABLE;

	/* Disable timer */
	writel(ctrl, clkevt_base + TIMER_CTRL);

	/* Enable the timer and start the periodic tick */
	writel(timer_reload, clkevt_base + TIMER_LOAD);
	ctrl |= TIMER_CTRL_PERIODIC | TIMER_CTRL_ENABLE;
	writel(ctrl, clkevt_base + TIMER_CTRL);
	return 0;
}