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
typedef  int u32 ;
struct sdw_master_prop {int mclk_freq; int hw_disabled; } ;
struct sdw_bus {int link_id; int /*<<< orphan*/  dev; struct sdw_master_prop prop; } ;
struct fwnode_handle {int dummy; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EIO ; 
 int SDW_INTEL_QUIRK_MASK_BUS_DISABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*) ; 
 struct fwnode_handle* device_get_named_child_node (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fwnode_property_read_u32 (struct fwnode_handle*,char*,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int sdw_master_read_intel_prop(struct sdw_bus *bus)
{
	struct sdw_master_prop *prop = &bus->prop;
	struct fwnode_handle *link;
	char name[32];
	u32 quirk_mask;

	/* Find master handle */
	snprintf(name, sizeof(name),
		 "mipi-sdw-link-%d-subproperties", bus->link_id);

	link = device_get_named_child_node(bus->dev, name);
	if (!link) {
		dev_err(bus->dev, "Master node %s not found\n", name);
		return -EIO;
	}

	fwnode_property_read_u32(link,
				 "intel-sdw-ip-clock",
				 &prop->mclk_freq);

	fwnode_property_read_u32(link,
				 "intel-quirk-mask",
				 &quirk_mask);

	if (quirk_mask & SDW_INTEL_QUIRK_MASK_BUS_DISABLE)
		prop->hw_disabled = true;

	return 0;
}