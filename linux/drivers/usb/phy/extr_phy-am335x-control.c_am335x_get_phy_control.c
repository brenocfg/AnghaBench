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
struct phy_control {int dummy; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct am335x_control_usb {struct phy_control phy_ctrl; } ;

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_node*,int /*<<< orphan*/ ) ; 
 struct am335x_control_usb* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  match ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct phy_control *am335x_get_phy_control(struct device *dev)
{
	struct device_node *node;
	struct am335x_control_usb *ctrl_usb;

	node = of_parse_phandle(dev->of_node, "ti,ctrl_mod", 0);
	if (!node)
		return NULL;

	dev = bus_find_device(&platform_bus_type, NULL, node, match);
	of_node_put(node);
	if (!dev)
		return NULL;

	ctrl_usb = dev_get_drvdata(dev);
	put_device(dev);
	if (!ctrl_usb)
		return NULL;
	return &ctrl_usb->phy_ctrl;
}