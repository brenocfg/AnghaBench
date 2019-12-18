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
struct v4l2_fwnode_bus_conv {int fwnode_bus_type; } ;
typedef  enum v4l2_fwnode_bus_type { ____Placeholder_v4l2_fwnode_bus_type } v4l2_fwnode_bus_type ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct v4l2_fwnode_bus_conv const*) ; 
 struct v4l2_fwnode_bus_conv const* buses ; 

__attribute__((used)) static const struct v4l2_fwnode_bus_conv *
get_v4l2_fwnode_bus_conv_by_fwnode_bus(enum v4l2_fwnode_bus_type type)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(buses); i++)
		if (buses[i].fwnode_bus_type == type)
			return &buses[i];

	return NULL;
}