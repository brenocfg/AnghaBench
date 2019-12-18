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
struct platform_device {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct platform_device* of_find_device_by_node (struct device_node*) ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int sun8i_dw_hdmi_find_connector_pdev(struct device *dev,
					     struct platform_device **pdev_out)
{
	struct platform_device *pdev;
	struct device_node *remote;

	remote = of_graph_get_remote_node(dev->of_node, 1, -1);
	if (!remote)
		return -ENODEV;

	if (!of_device_is_compatible(remote, "hdmi-connector")) {
		of_node_put(remote);
		return -ENODEV;
	}

	pdev = of_find_device_by_node(remote);
	of_node_put(remote);
	if (!pdev)
		return -ENODEV;

	*pdev_out = pdev;
	return 0;
}