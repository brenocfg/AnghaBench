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
struct mcu {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_status ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mcu* glob_mcu ; 
 struct mcu* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct mcu*) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 int mcu_gpiochip_remove (struct mcu*) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  shutdown_thread ; 

__attribute__((used)) static int mcu_remove(struct i2c_client *client)
{
	struct mcu *mcu = i2c_get_clientdata(client);
	int ret;

	kthread_stop(shutdown_thread);

	device_remove_file(&client->dev, &dev_attr_status);

	if (glob_mcu == mcu) {
		pm_power_off = NULL;
		glob_mcu = NULL;
	}

	ret = mcu_gpiochip_remove(mcu);
	if (ret)
		return ret;
	kfree(mcu);
	return 0;
}