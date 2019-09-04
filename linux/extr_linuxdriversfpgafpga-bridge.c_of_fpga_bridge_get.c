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
struct fpga_image_info {int dummy; } ;
struct fpga_bridge {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct fpga_bridge* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct fpga_bridge* __fpga_bridge_get (struct device*,struct fpga_image_info*) ; 
 struct device* class_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_bridge_class ; 
 int /*<<< orphan*/  fpga_bridge_of_node_match ; 

struct fpga_bridge *of_fpga_bridge_get(struct device_node *np,
				       struct fpga_image_info *info)
{
	struct device *dev;

	dev = class_find_device(fpga_bridge_class, NULL, np,
				fpga_bridge_of_node_match);
	if (!dev)
		return ERR_PTR(-ENODEV);

	return __fpga_bridge_get(dev, info);
}