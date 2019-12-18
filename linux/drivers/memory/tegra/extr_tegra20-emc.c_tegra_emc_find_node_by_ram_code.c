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
typedef  scalar_t__ u32 ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 struct device_node* of_find_node_by_name (struct device_node*,char*) ; 
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 scalar_t__ tegra_read_ram_code () ; 

__attribute__((used)) static struct device_node *
tegra_emc_find_node_by_ram_code(struct device *dev)
{
	struct device_node *np;
	u32 value, ram_code;
	int err;

	if (!of_property_read_bool(dev->of_node, "nvidia,use-ram-code"))
		return of_node_get(dev->of_node);

	ram_code = tegra_read_ram_code();

	for (np = of_find_node_by_name(dev->of_node, "emc-tables"); np;
	     np = of_find_node_by_name(np, "emc-tables")) {
		err = of_property_read_u32(np, "nvidia,ram-code", &value);
		if (err || value != ram_code) {
			of_node_put(np);
			continue;
		}

		return np;
	}

	dev_err(dev, "no memory timings for RAM code %u found in device tree\n",
		ram_code);

	return NULL;
}