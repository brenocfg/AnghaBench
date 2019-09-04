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
struct device_node {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ WARN_ON (int) ; 
 struct device* class_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  vexpress_config_class ; 
 int /*<<< orphan*/  vexpress_config_node_match ; 

__attribute__((used)) static int vexpress_config_populate(struct device_node *node)
{
	struct device_node *bridge;
	struct device *parent;
	int ret;

	bridge = of_parse_phandle(node, "arm,vexpress,config-bridge", 0);
	if (!bridge)
		return -EINVAL;

	parent = class_find_device(vexpress_config_class, NULL, bridge,
			vexpress_config_node_match);
	of_node_put(bridge);
	if (WARN_ON(!parent))
		return -ENODEV;

	ret = of_platform_populate(node, NULL, NULL, parent);

	put_device(parent);

	return ret;
}