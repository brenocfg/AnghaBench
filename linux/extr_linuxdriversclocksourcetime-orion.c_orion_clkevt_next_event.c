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
 int TIMER1_EN ; 
 int TIMER1_RELOAD_EN ; 
 scalar_t__ TIMER1_VAL ; 
 scalar_t__ TIMER_CTRL ; 
 int /*<<< orphan*/  atomic_io_modify (scalar_t__,int,int) ; 
 scalar_t__ timer_base ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static int orion_clkevt_next_event(unsigned long delta,
				   struct clock_event_device *dev)
{
	/* setup and enable one-shot timer */
	writel(delta, timer_base + TIMER1_VAL);
	atomic_io_modify(timer_base + TIMER_CTRL,
		TIMER1_RELOAD_EN | TIMER1_EN, TIMER1_EN);

	return 0;
}