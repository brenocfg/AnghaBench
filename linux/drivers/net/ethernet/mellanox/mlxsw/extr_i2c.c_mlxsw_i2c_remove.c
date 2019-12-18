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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mlxsw_i2c {TYPE_1__ cmd; int /*<<< orphan*/  core; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct mlxsw_i2c* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  mlxsw_core_bus_device_unregister (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlxsw_i2c_remove(struct i2c_client *client)
{
	struct mlxsw_i2c *mlxsw_i2c = i2c_get_clientdata(client);

	mlxsw_core_bus_device_unregister(mlxsw_i2c->core, false);
	mutex_destroy(&mlxsw_i2c->cmd.lock);

	return 0;
}