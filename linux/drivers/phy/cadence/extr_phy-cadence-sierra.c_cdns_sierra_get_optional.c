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
struct cdns_sierra_inst {int /*<<< orphan*/  phy_type; int /*<<< orphan*/  num_lanes; int /*<<< orphan*/  mlane; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cdns_sierra_get_optional(struct cdns_sierra_inst *inst,
				    struct device_node *child)
{
	if (of_property_read_u32(child, "reg", &inst->mlane))
		return -EINVAL;

	if (of_property_read_u32(child, "cdns,num-lanes", &inst->num_lanes))
		return -EINVAL;

	if (of_property_read_u32(child, "cdns,phy-type", &inst->phy_type))
		return -EINVAL;

	return 0;
}