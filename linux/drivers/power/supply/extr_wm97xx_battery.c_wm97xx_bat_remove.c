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
struct wm97xx_batt_pdata {int /*<<< orphan*/  charge_gpio; } ;
struct TYPE_2__ {struct wm97xx_batt_pdata* platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bat_psy ; 
 int /*<<< orphan*/  bat_work ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct platform_device*) ; 
 int /*<<< orphan*/  gpio_free (int /*<<< orphan*/ ) ; 
 scalar_t__ gpio_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_to_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop ; 

__attribute__((used)) static int wm97xx_bat_remove(struct platform_device *dev)
{
	struct wm97xx_batt_pdata *pdata = dev->dev.platform_data;

	if (pdata && gpio_is_valid(pdata->charge_gpio)) {
		free_irq(gpio_to_irq(pdata->charge_gpio), dev);
		gpio_free(pdata->charge_gpio);
	}
	cancel_work_sync(&bat_work);
	power_supply_unregister(bat_psy);
	kfree(prop);
	return 0;
}