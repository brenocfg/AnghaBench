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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*,...) ; 
 struct device_node* of_get_child_regulator (int /*<<< orphan*/ ,char*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static struct device_node *of_get_regulator(struct device *dev, const char *supply)
{
	struct device_node *regnode = NULL;
	char prop_name[32]; /* 32 is max size of property name */

	dev_dbg(dev, "Looking up %s-supply from device tree\n", supply);

	snprintf(prop_name, 32, "%s-supply", supply);
	regnode = of_parse_phandle(dev->of_node, prop_name, 0);

	if (!regnode) {
		regnode = of_get_child_regulator(dev->of_node, prop_name);
		if (regnode)
			return regnode;

		dev_dbg(dev, "Looking up %s property in node %pOF failed\n",
				prop_name, dev->of_node);
		return NULL;
	}
	return regnode;
}