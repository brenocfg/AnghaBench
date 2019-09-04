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
 scalar_t__ clockevent_state_oneshot (struct clock_event_device*) ; 
 int /*<<< orphan*/  sprd_timer_clear_interrupt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprd_timer_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  timer_of_base (struct timer_of*) ; 
 struct timer_of* to_timer_of (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t sprd_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *ce = (struct clock_event_device *)dev_id;
	struct timer_of *to = to_timer_of(ce);

	sprd_timer_clear_interrupt(timer_of_base(to));

	if (clockevent_state_oneshot(ce))
		sprd_timer_disable(timer_of_base(to));

	ce->event_handler(ce);
	return IRQ_HANDLED;
}