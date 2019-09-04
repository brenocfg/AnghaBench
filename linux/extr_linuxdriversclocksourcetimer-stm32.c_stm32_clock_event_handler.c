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
struct timer_of {int dummy; } ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TIM_SR ; 
 scalar_t__ clockevent_state_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  stm32_clock_event_set_periodic (struct clock_event_device*) ; 
 int /*<<< orphan*/  stm32_clock_event_shutdown (struct clock_event_device*) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 scalar_t__ timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t stm32_clock_event_handler(int irq, void *dev_id)
{
	struct clock_event_device *clkevt = (struct clock_event_device *)dev_id;
	struct timer_of *to = to_timer_of(clkevt);

	writel_relaxed(0, timer_of_base(to) + TIM_SR);

	if (clockevent_state_periodic(clkevt))
		stm32_clock_event_set_periodic(clkevt);
	else
		stm32_clock_event_shutdown(clkevt);

	clkevt->event_handler(clkevt);

	return IRQ_HANDLED;
}