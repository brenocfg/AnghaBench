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
typedef  int u8 ;
typedef  int u32 ;
struct ab3100 {int startup_events_read; int* startup_events; int /*<<< orphan*/  dev; int /*<<< orphan*/  event_subscribers; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AB3100_EVENTA1 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ab3100_get_register_page_interruptible (struct ab3100*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static irqreturn_t ab3100_irq_handler(int irq, void *data)
{
	struct ab3100 *ab3100 = data;
	u8 event_regs[3];
	u32 fatevent;
	int err;

	err = ab3100_get_register_page_interruptible(ab3100, AB3100_EVENTA1,
				       event_regs, 3);
	if (err)
		goto err_event;

	fatevent = (event_regs[0] << 16) |
		(event_regs[1] << 8) |
		event_regs[2];

	if (!ab3100->startup_events_read) {
		ab3100->startup_events[0] = event_regs[0];
		ab3100->startup_events[1] = event_regs[1];
		ab3100->startup_events[2] = event_regs[2];
		ab3100->startup_events_read = true;
	}
	/*
	 * The notified parties will have to mask out the events
	 * they're interested in and react to them. They will be
	 * notified on all events, then they use the fatevent value
	 * to determine if they're interested.
	 */
	blocking_notifier_call_chain(&ab3100->event_subscribers,
				     fatevent, NULL);

	dev_dbg(ab3100->dev,
		"IRQ Event: 0x%08x\n", fatevent);

	return IRQ_HANDLED;

 err_event:
	dev_dbg(ab3100->dev,
		"error reading event status\n");
	return IRQ_HANDLED;
}