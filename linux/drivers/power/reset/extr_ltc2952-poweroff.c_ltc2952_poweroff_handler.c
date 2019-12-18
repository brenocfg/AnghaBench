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
struct ltc2952_poweroff {int /*<<< orphan*/  timer_trigger; int /*<<< orphan*/  trigger_delay; int /*<<< orphan*/  gpio_trigger; int /*<<< orphan*/  timer_wde; scalar_t__ kernel_panic; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ gpiod_get_value (int /*<<< orphan*/ ) ; 
 scalar_t__ hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ltc2952_poweroff_handler(int irq, void *dev_id)
{
	struct ltc2952_poweroff *data = dev_id;

	if (data->kernel_panic || hrtimer_active(&data->timer_wde)) {
		/* shutdown is already triggered, nothing to do any more */
		return IRQ_HANDLED;
	}

	if (gpiod_get_value(data->gpio_trigger)) {
		hrtimer_start(&data->timer_trigger, data->trigger_delay,
			      HRTIMER_MODE_REL);
	} else {
		hrtimer_cancel(&data->timer_trigger);
	}
	return IRQ_HANDLED;
}