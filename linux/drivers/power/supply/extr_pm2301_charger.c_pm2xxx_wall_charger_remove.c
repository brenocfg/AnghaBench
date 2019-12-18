#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  psy; } ;
struct pm2xxx_charger {int /*<<< orphan*/  lpn_pin; TYPE_2__ ac_chg; int /*<<< orphan*/  regu; int /*<<< orphan*/  charger_wq; TYPE_1__* pdata; int /*<<< orphan*/  dev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  gpio_irq_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pm2xxx_charger*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 struct pm2xxx_charger* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct pm2xxx_charger*) ; 
 int /*<<< orphan*/  pm2xxx_charger_ac_en (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm2xxx_wall_charger_remove(struct i2c_client *i2c_client)
{
	struct pm2xxx_charger *pm2 = i2c_get_clientdata(i2c_client);

	/* Disable pm_runtime */
	pm_runtime_disable(pm2->dev);
	/* Disable AC charging */
	pm2xxx_charger_ac_en(&pm2->ac_chg, false, 0, 0);

	/* Disable wake by pm interrupt */
	disable_irq_wake(gpio_to_irq(pm2->pdata->gpio_irq_number));

	/* Disable interrupts */
	free_irq(gpio_to_irq(pm2->pdata->gpio_irq_number), pm2);

	/* Delete the work queue */
	destroy_workqueue(pm2->charger_wq);

	flush_scheduled_work();

	/* disable the regulator */
	regulator_put(pm2->regu);

	power_supply_unregister(pm2->ac_chg.psy);

	if (gpio_is_valid(pm2->lpn_pin))
		gpio_free(pm2->lpn_pin);

	kfree(pm2);

	return 0;
}