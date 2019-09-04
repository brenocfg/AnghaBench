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
typedef  int const u8 ;
typedef  int u32 ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 

u8 pmac_i2c_get_dev_addr(struct device_node *device)
{
	const u32 *reg = of_get_property(device, "reg", NULL);

	if (reg == NULL)
		return 0;

	return (*reg) & 0xff;
}