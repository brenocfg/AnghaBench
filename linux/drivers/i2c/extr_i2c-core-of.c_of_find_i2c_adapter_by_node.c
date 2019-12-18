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
struct i2c_adapter {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_bus_type ; 
 struct i2c_adapter* i2c_verify_adapter (struct device*) ; 
 int /*<<< orphan*/  of_dev_or_parent_node_match ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct i2c_adapter *of_find_i2c_adapter_by_node(struct device_node *node)
{
	struct device *dev;
	struct i2c_adapter *adapter;

	dev = bus_find_device(&i2c_bus_type, NULL, node,
			      of_dev_or_parent_node_match);
	if (!dev)
		return NULL;

	adapter = i2c_verify_adapter(dev);
	if (!adapter)
		put_device(dev);

	return adapter;
}