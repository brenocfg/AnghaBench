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
struct i2c_adapter {int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct i2c_adapter* of_find_i2c_adapter_by_node (struct device_node*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct i2c_adapter *of_get_i2c_adapter_by_node(struct device_node *node)
{
	struct i2c_adapter *adapter;

	adapter = of_find_i2c_adapter_by_node(node);
	if (!adapter)
		return NULL;

	if (!try_module_get(adapter->owner)) {
		put_device(&adapter->dev);
		adapter = NULL;
	}

	return adapter;
}