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
struct extcon_dev {int dummy; } ;
struct dwc3 {struct device* dev; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct extcon_dev* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ device_property_read_bool (struct device*,char*) ; 
 scalar_t__ device_property_read_string (struct device*,char*,char const**) ; 
 struct extcon_dev* extcon_find_edev_by_node (struct device_node*) ; 
 struct extcon_dev* extcon_get_edev_by_phandle (struct device*,int /*<<< orphan*/ ) ; 
 struct extcon_dev* extcon_get_extcon_dev (char const*) ; 
 struct device_node* of_graph_get_remote_node (struct device_node*,int,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct extcon_dev *dwc3_get_extcon(struct dwc3 *dwc)
{
	struct device *dev = dwc->dev;
	struct device_node *np_phy, *np_conn;
	struct extcon_dev *edev;
	const char *name;

	if (device_property_read_bool(dev, "extcon"))
		return extcon_get_edev_by_phandle(dev, 0);

	/*
	 * Device tree platforms should get extcon via phandle.
	 * On ACPI platforms, we get the name from a device property.
	 * This device property is for kernel internal use only and
	 * is expected to be set by the glue code.
	 */
	if (device_property_read_string(dev, "linux,extcon-name", &name) == 0) {
		edev = extcon_get_extcon_dev(name);
		if (!edev)
			return ERR_PTR(-EPROBE_DEFER);

		return edev;
	}

	np_phy = of_parse_phandle(dev->of_node, "phys", 0);
	np_conn = of_graph_get_remote_node(np_phy, -1, -1);

	if (np_conn)
		edev = extcon_find_edev_by_node(np_conn);
	else
		edev = NULL;

	of_node_put(np_conn);
	of_node_put(np_phy);

	return edev;
}