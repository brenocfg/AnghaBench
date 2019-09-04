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
struct cros_ec_device {int /*<<< orphan*/  event_notifier; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  blocking_notifier_call_chain (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct cros_ec_device*) ; 
 int cros_ec_get_next_event (struct cros_ec_device*,int*) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ec_irq_thread(int irq, void *data)
{
	struct cros_ec_device *ec_dev = data;
	bool wake_event = true;
	int ret;

	ret = cros_ec_get_next_event(ec_dev, &wake_event);

	/*
	 * Signal only if wake host events or any interrupt if
	 * cros_ec_get_next_event() returned an error (default value for
	 * wake_event is true)
	 */
	if (wake_event && device_may_wakeup(ec_dev->dev))
		pm_wakeup_event(ec_dev->dev, 0);

	if (ret > 0)
		blocking_notifier_call_chain(&ec_dev->event_notifier,
					     0, ec_dev);
	return IRQ_HANDLED;
}