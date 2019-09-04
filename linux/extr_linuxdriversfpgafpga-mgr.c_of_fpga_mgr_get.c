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
struct fpga_manager {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 struct fpga_manager* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct fpga_manager* __fpga_mgr_get (struct device*) ; 
 struct device* class_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga_mgr_class ; 
 int /*<<< orphan*/  fpga_mgr_of_node_match ; 

struct fpga_manager *of_fpga_mgr_get(struct device_node *node)
{
	struct device *dev;

	dev = class_find_device(fpga_mgr_class, NULL, node,
				fpga_mgr_of_node_match);
	if (!dev)
		return ERR_PTR(-ENODEV);

	return __fpga_mgr_get(dev);
}