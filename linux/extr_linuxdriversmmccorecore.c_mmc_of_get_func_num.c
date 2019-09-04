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
struct device_node {int dummy; } ;

/* Variables and functions */
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int mmc_of_get_func_num(struct device_node *node)
{
	u32 reg;
	int ret;

	ret = of_property_read_u32(node, "reg", &reg);
	if (ret < 0)
		return ret;

	return reg;
}