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
struct device {int /*<<< orphan*/ * type; struct device* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_adapter_type ; 
 struct i2c_adapter* i2c_parent_is_i2c_adapter (struct i2c_adapter*) ; 
 struct i2c_adapter* to_i2c_adapter (struct device*) ; 

struct i2c_adapter *i2c_root_adapter(struct device *dev)
{
	struct device *i2c;
	struct i2c_adapter *i2c_root;

	/*
	 * Walk up the device tree to find an i2c adapter, indicating
	 * that this is an i2c client device. Check all ancestors to
	 * handle mfd devices etc.
	 */
	for (i2c = dev; i2c; i2c = i2c->parent) {
		if (i2c->type == &i2c_adapter_type)
			break;
	}
	if (!i2c)
		return NULL;

	/* Continue up the tree to find the root i2c adapter */
	i2c_root = to_i2c_adapter(i2c);
	while (i2c_parent_is_i2c_adapter(i2c_root))
		i2c_root = i2c_parent_is_i2c_adapter(i2c_root);

	return i2c_root;
}