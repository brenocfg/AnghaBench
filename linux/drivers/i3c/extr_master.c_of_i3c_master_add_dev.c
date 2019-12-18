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
typedef  int /*<<< orphan*/  u32 ;
struct i3c_master_controller {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int of_i3c_master_add_i2c_boardinfo (struct i3c_master_controller*,struct device_node*,int /*<<< orphan*/ *) ; 
 int of_i3c_master_add_i3c_boardinfo (struct i3c_master_controller*,struct device_node*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32_array (struct device_node*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_i3c_master_add_dev(struct i3c_master_controller *master,
				 struct device_node *node)
{
	u32 reg[3];
	int ret;

	if (!master || !node)
		return -EINVAL;

	ret = of_property_read_u32_array(node, "reg", reg, ARRAY_SIZE(reg));
	if (ret)
		return ret;

	/*
	 * The manufacturer ID can't be 0. If reg[1] == 0 that means we're
	 * dealing with an I2C device.
	 */
	if (!reg[1])
		ret = of_i3c_master_add_i2c_boardinfo(master, node, reg);
	else
		ret = of_i3c_master_add_i3c_boardinfo(master, node, reg);

	return ret;
}