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
struct i2c_client {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fwnode; } ;
struct fusb302_chip {int /*<<< orphan*/  wq; TYPE_1__ tcpc_dev; int /*<<< orphan*/  tcpm_port; int /*<<< orphan*/  bc_lvl_handler; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  gpio_int_n_irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fusb302_chip*) ; 
 int /*<<< orphan*/  fusb302_debugfs_exit (struct fusb302_chip*) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 struct fusb302_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  tcpm_unregister_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fusb302_remove(struct i2c_client *client)
{
	struct fusb302_chip *chip = i2c_get_clientdata(client);

	disable_irq_wake(chip->gpio_int_n_irq);
	free_irq(chip->gpio_int_n_irq, chip);
	cancel_work_sync(&chip->irq_work);
	cancel_delayed_work_sync(&chip->bc_lvl_handler);
	tcpm_unregister_port(chip->tcpm_port);
	fwnode_handle_put(chip->tcpc_dev.fwnode);
	destroy_workqueue(chip->wq);
	fusb302_debugfs_exit(chip);

	return 0;
}