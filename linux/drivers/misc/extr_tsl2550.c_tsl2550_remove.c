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
struct TYPE_2__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsl2550_attr_group ; 
 int /*<<< orphan*/  tsl2550_set_power_state (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tsl2550_remove(struct i2c_client *client)
{
	sysfs_remove_group(&client->dev.kobj, &tsl2550_attr_group);

	/* Power down the device */
	tsl2550_set_power_state(client, 0);

	kfree(i2c_get_clientdata(client));

	return 0;
}