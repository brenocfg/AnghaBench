#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int als_set_default_config (struct i2c_client*) ; 
 int /*<<< orphan*/  als_set_power_state (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_als_gr ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int  isl29020_probe(struct i2c_client *client,
					const struct i2c_device_id *id)
{
	int res;

	res = als_set_default_config(client);
	if (res <  0)
		return res;

	res = sysfs_create_group(&client->dev.kobj, &m_als_gr);
	if (res) {
		dev_err(&client->dev, "isl29020: device create file failed\n");
		return res;
	}
	dev_info(&client->dev, "%s isl29020: ALS chip found\n", client->name);
	als_set_power_state(client, 0);
	pm_runtime_enable(&client->dev);
	return res;
}