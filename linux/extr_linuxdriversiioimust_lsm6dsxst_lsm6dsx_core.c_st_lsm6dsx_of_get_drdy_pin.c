#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_lsm6dsx_hw {TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 

__attribute__((used)) static int st_lsm6dsx_of_get_drdy_pin(struct st_lsm6dsx_hw *hw, int *drdy_pin)
{
	struct device_node *np = hw->dev->of_node;

	if (!np)
		return -EINVAL;

	return of_property_read_u32(np, "st,drdy-int-pin", drdy_pin);
}