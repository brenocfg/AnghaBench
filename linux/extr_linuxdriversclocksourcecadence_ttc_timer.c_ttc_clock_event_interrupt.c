#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;
struct ttc_timer {scalar_t__ base_addr; } ;
struct ttc_timer_clockevent {TYPE_1__ ce; struct ttc_timer ttc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ TTC_ISR_OFFSET ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static irqreturn_t ttc_clock_event_interrupt(int irq, void *dev_id)
{
	struct ttc_timer_clockevent *ttce = dev_id;
	struct ttc_timer *timer = &ttce->ttc;

	/* Acknowledge the interrupt and call event handler */
	readl_relaxed(timer->base_addr + TTC_ISR_OFFSET);

	ttce->ce.event_handler(&ttce->ce);

	return IRQ_HANDLED;
}