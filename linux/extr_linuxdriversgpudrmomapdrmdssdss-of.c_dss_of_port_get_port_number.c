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

/* Variables and functions */
 int of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

u32 dss_of_port_get_port_number(struct device_node *port)
{
	int r;
	u32 reg;

	r = of_property_read_u32(port, "reg", &reg);
	if (r)
		reg = 0;

	return reg;
}