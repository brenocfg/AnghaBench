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
struct retu_dev {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  dev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 struct retu_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct retu_dev* retu_pm_power_off ; 

__attribute__((used)) static int retu_remove(struct i2c_client *i2c)
{
	struct retu_dev *rdev = i2c_get_clientdata(i2c);

	if (retu_pm_power_off == rdev) {
		pm_power_off	  = NULL;
		retu_pm_power_off = NULL;
	}
	mfd_remove_devices(rdev->dev);
	regmap_del_irq_chip(i2c->irq, rdev->irq_data);

	return 0;
}