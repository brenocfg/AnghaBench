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
struct device {scalar_t__ of_node; } ;
struct i2c_adapter {int nr; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN (int,char*) ; 
 int __i2c_add_numbered_adapter (struct i2c_adapter*) ; 
 int /*<<< orphan*/  __i2c_first_dynamic_bus_num ; 
 int /*<<< orphan*/  core_lock ; 
 int /*<<< orphan*/  i2c_adapter_idr ; 
 int i2c_register_adapter (struct i2c_adapter*) ; 
 int idr_alloc (int /*<<< orphan*/ *,struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int of_alias_get_id (scalar_t__,char*) ; 

int i2c_add_adapter(struct i2c_adapter *adapter)
{
	struct device *dev = &adapter->dev;
	int id;

	if (dev->of_node) {
		id = of_alias_get_id(dev->of_node, "i2c");
		if (id >= 0) {
			adapter->nr = id;
			return __i2c_add_numbered_adapter(adapter);
		}
	}

	mutex_lock(&core_lock);
	id = idr_alloc(&i2c_adapter_idr, adapter,
		       __i2c_first_dynamic_bus_num, 0, GFP_KERNEL);
	mutex_unlock(&core_lock);
	if (WARN(id < 0, "couldn't get idr"))
		return id;

	adapter->nr = id;

	return i2c_register_adapter(adapter);
}