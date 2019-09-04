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
struct si476x_core {int /*<<< orphan*/  gpio_reset; int /*<<< orphan*/  rds_fifo; int /*<<< orphan*/  status_monitor; } ;
struct i2c_client {scalar_t__ irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (scalar_t__) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 struct si476x_core* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  si476x_core_pronounce_dead (struct si476x_core*) ; 

__attribute__((used)) static int si476x_core_remove(struct i2c_client *client)
{
	struct si476x_core *core = i2c_get_clientdata(client);

	si476x_core_pronounce_dead(core);
	mfd_remove_devices(&client->dev);

	if (client->irq)
		disable_irq(client->irq);
	else
		cancel_delayed_work_sync(&core->status_monitor);

	kfifo_free(&core->rds_fifo);

	if (gpio_is_valid(core->gpio_reset))
		gpio_free(core->gpio_reset);

	return 0;
}