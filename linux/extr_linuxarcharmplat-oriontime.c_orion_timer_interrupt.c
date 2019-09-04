#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_3__ {int /*<<< orphan*/  (* event_handler ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ BRIDGE_CAUSE_OFF ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ bridge_base ; 
 int /*<<< orphan*/  bridge_timer1_clr_mask ; 
 TYPE_1__ orion_clkevt ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t orion_timer_interrupt(int irq, void *dev_id)
{
	/*
	 * ACK timer interrupt and call event handler.
	 */
	writel(bridge_timer1_clr_mask, bridge_base + BRIDGE_CAUSE_OFF);
	orion_clkevt.event_handler(&orion_clkevt);

	return IRQ_HANDLED;
}