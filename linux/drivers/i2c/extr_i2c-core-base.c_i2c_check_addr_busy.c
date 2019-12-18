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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int device_for_each_child (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_mux_children ; 
 int i2c_check_mux_parents (struct i2c_adapter*,int) ; 
 struct i2c_adapter* i2c_parent_is_i2c_adapter (struct i2c_adapter*) ; 

__attribute__((used)) static int i2c_check_addr_busy(struct i2c_adapter *adapter, int addr)
{
	struct i2c_adapter *parent = i2c_parent_is_i2c_adapter(adapter);
	int result = 0;

	if (parent)
		result = i2c_check_mux_parents(parent, addr);

	if (!result)
		result = device_for_each_child(&adapter->dev, &addr,
						i2c_check_mux_children);

	return result;
}