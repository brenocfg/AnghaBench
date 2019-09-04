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
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ SIRFSOC_TIMER_STATUS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int readl_relaxed (scalar_t__) ; 
 scalar_t__ sirfsoc_timer_base ; 
 int /*<<< orphan*/  stub1 (struct clock_event_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sirfsoc_timer_interrupt(int irq, void *dev_id)
{
	struct clock_event_device *ce = dev_id;

	WARN_ON(!(readl_relaxed(sirfsoc_timer_base + SIRFSOC_TIMER_STATUS) &
		BIT(0)));

	/* clear timer0 interrupt */
	writel_relaxed(BIT(0), sirfsoc_timer_base + SIRFSOC_TIMER_STATUS);

	ce->event_handler(ce);

	return IRQ_HANDLED;
}