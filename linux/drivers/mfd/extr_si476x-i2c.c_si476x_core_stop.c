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
struct si476x_power_down_args {int xosc; } ;
struct si476x_core {int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  status_monitor; TYPE_1__* client; int /*<<< orphan*/  is_alive; } ;
struct TYPE_2__ {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si476x_core_cmd_power_down (struct si476x_core*,struct si476x_power_down_args*) ; 

int si476x_core_stop(struct si476x_core *core, bool soft)
{
	int err = 0;
	atomic_set(&core->is_alive, 0);

	if (soft) {
		/* TODO: This probably shoud be a configurable option,
		 * so it is possible to have the chips keep their
		 * oscillators running
		 */
		struct si476x_power_down_args args = {
			.xosc = false,
		};
		err = si476x_core_cmd_power_down(core, &args);
	}

	/* We couldn't disable those before
	 * 'si476x_core_cmd_power_down' since we expect to get CTS
	 * interrupt */
	if (core->client->irq)
		disable_irq(core->client->irq);
	else
		cancel_delayed_work_sync(&core->status_monitor);

	if (!soft) {
		if (gpio_is_valid(core->gpio_reset))
			gpio_set_value_cansleep(core->gpio_reset, 0);
	}
	return err;
}