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
struct device {int /*<<< orphan*/  parent; int /*<<< orphan*/  of_node; } ;
struct fpga_bridge {int /*<<< orphan*/  name; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 

int fpga_bridge_register(struct fpga_bridge *bridge)
{
	struct device *dev = &bridge->dev;
	int ret;

	ret = device_add(dev);
	if (ret)
		return ret;

	of_platform_populate(dev->of_node, NULL, NULL, dev);

	dev_info(dev->parent, "fpga bridge [%s] registered\n", bridge->name);

	return 0;
}