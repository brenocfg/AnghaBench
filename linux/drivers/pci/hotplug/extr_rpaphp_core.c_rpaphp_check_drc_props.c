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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FW_FEATURE_DRC_INFO ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 unsigned int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int rpaphp_check_drc_props_v1 (struct device_node*,char*,char*,unsigned int const) ; 
 int rpaphp_check_drc_props_v2 (struct device_node*,char*,char*,unsigned int const) ; 

int rpaphp_check_drc_props(struct device_node *dn, char *drc_name,
			char *drc_type)
{
	const unsigned int *my_index;

	my_index = of_get_property(dn, "ibm,my-drc-index", NULL);
	if (!my_index) {
		/* Node isn't DLPAR/hotplug capable */
		return -EINVAL;
	}

	if (firmware_has_feature(FW_FEATURE_DRC_INFO))
		return rpaphp_check_drc_props_v2(dn, drc_name, drc_type,
						*my_index);
	else
		return rpaphp_check_drc_props_v1(dn, drc_name, drc_type,
						*my_index);
}