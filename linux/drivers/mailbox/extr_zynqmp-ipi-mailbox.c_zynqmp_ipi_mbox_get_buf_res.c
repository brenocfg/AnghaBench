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
struct resource {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int of_address_to_resource (struct device_node*,int,struct resource*) ; 
 int of_property_match_string (struct device_node*,char*,char const*) ; 

__attribute__((used)) static int zynqmp_ipi_mbox_get_buf_res(struct device_node *node,
				       const char *name,
				       struct resource *res)
{
	int ret, index;

	index = of_property_match_string(node, "reg-names", name);
	if (index >= 0) {
		ret = of_address_to_resource(node, index, res);
		if (ret < 0)
			return -EINVAL;
		return 0;
	}
	return -ENODEV;
}