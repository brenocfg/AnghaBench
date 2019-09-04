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
struct dw_apb_clock_event_device {int /*<<< orphan*/  timer; int /*<<< orphan*/  (* eoi ) (int /*<<< orphan*/ *) ;} ;
struct clock_event_device {int /*<<< orphan*/  (* event_handler ) (struct clock_event_device*) ;} ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 struct dw_apb_clock_event_device* ced_to_dw_apb_ced (struct clock_event_device*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct clock_event_device*) ; 

__attribute__((used)) static irqreturn_t dw_apb_clockevent_irq(int irq, void *data)
{
	struct clock_event_device *evt = data;
	struct dw_apb_clock_event_device *dw_ced = ced_to_dw_apb_ced(evt);

	if (!evt->event_handler) {
		pr_info("Spurious APBT timer interrupt %d\n", irq);
		return IRQ_NONE;
	}

	if (dw_ced->eoi)
		dw_ced->eoi(&dw_ced->timer);

	evt->event_handler(evt);
	return IRQ_HANDLED;
}