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
struct regulator_dev {struct regulator_desc* desc; } ;
struct regulator_desc {TYPE_1__* ops; } ;
struct TYPE_2__ {int (* map_voltage ) (struct regulator_dev*,int,int) ;scalar_t__ list_voltage; } ;

/* Variables and functions */
 scalar_t__ regulator_list_voltage_linear ; 
 scalar_t__ regulator_list_voltage_linear_range ; 
 scalar_t__ regulator_list_voltage_pickable_linear_range ; 
 int regulator_map_voltage_iterate (struct regulator_dev*,int,int) ; 
 int regulator_map_voltage_linear (struct regulator_dev*,int,int) ; 
 int regulator_map_voltage_linear_range (struct regulator_dev*,int,int) ; 
 int regulator_map_voltage_pickable_linear_range (struct regulator_dev*,int,int) ; 
 int stub1 (struct regulator_dev*,int,int) ; 

__attribute__((used)) static int regulator_map_voltage(struct regulator_dev *rdev, int min_uV,
				 int max_uV)
{
	const struct regulator_desc *desc = rdev->desc;

	if (desc->ops->map_voltage)
		return desc->ops->map_voltage(rdev, min_uV, max_uV);

	if (desc->ops->list_voltage == regulator_list_voltage_linear)
		return regulator_map_voltage_linear(rdev, min_uV, max_uV);

	if (desc->ops->list_voltage == regulator_list_voltage_linear_range)
		return regulator_map_voltage_linear_range(rdev, min_uV, max_uV);

	if (desc->ops->list_voltage ==
		regulator_list_voltage_pickable_linear_range)
		return regulator_map_voltage_pickable_linear_range(rdev,
							min_uV, max_uV);

	return regulator_map_voltage_iterate(rdev, min_uV, max_uV);
}