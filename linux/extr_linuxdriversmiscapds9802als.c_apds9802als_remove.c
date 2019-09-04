#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kobj; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct als_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  als_set_power_state (struct i2c_client*,int) ; 
 struct als_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct als_data*) ; 
 int /*<<< orphan*/  m_als_gr ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds9802als_remove(struct i2c_client *client)
{
	struct als_data *data = i2c_get_clientdata(client);

	pm_runtime_get_sync(&client->dev);

	als_set_power_state(client, false);
	sysfs_remove_group(&client->dev.kobj, &m_als_gr);

	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);
	pm_runtime_put_noidle(&client->dev);

	kfree(data);
	return 0;
}