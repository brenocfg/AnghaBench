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
struct i2c_driver {int /*<<< orphan*/  remove; int /*<<< orphan*/  probe; } ;

/* Variables and functions */
 int i2c_add_driver (struct i2c_driver*) ; 
 int /*<<< orphan*/  mlxsw_i2c_probe ; 
 int /*<<< orphan*/  mlxsw_i2c_remove ; 

int mlxsw_i2c_driver_register(struct i2c_driver *i2c_driver)
{
	i2c_driver->probe = mlxsw_i2c_probe;
	i2c_driver->remove = mlxsw_i2c_remove;
	return i2c_add_driver(i2c_driver);
}