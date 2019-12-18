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
struct i2c_client {int dummy; } ;
struct bq24190_dev_info {int /*<<< orphan*/  dev; scalar_t__ charger; scalar_t__ battery; } ;

/* Variables and functions */
 int /*<<< orphan*/  bq24190_register_reset (struct bq24190_dev_info*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 struct bq24190_dev_info* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_dont_use_autosuspend (int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  power_supply_unregister (scalar_t__) ; 

__attribute__((used)) static int bq24190_remove(struct i2c_client *client)
{
	struct bq24190_dev_info *bdi = i2c_get_clientdata(client);
	int error;

	error = pm_runtime_get_sync(bdi->dev);
	if (error < 0) {
		dev_warn(bdi->dev, "pm_runtime_get failed: %i\n", error);
		pm_runtime_put_noidle(bdi->dev);
	}

	bq24190_register_reset(bdi);
	if (bdi->battery)
		power_supply_unregister(bdi->battery);
	power_supply_unregister(bdi->charger);
	if (error >= 0)
		pm_runtime_put_sync(bdi->dev);
	pm_runtime_dont_use_autosuspend(bdi->dev);
	pm_runtime_disable(bdi->dev);

	return 0;
}