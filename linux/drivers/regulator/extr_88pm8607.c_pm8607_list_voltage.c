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
struct regulator_dev {int dummy; } ;
struct pm8607_regulator_info {scalar_t__ slope_double; } ;

/* Variables and functions */
 struct pm8607_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regulator_list_voltage_table (struct regulator_dev*,unsigned int) ; 

__attribute__((used)) static int pm8607_list_voltage(struct regulator_dev *rdev, unsigned index)
{
	struct pm8607_regulator_info *info = rdev_get_drvdata(rdev);
	int ret;

	ret = regulator_list_voltage_table(rdev, index);
	if (ret < 0)
		return ret;

	if (info->slope_double)
		ret <<= 1;

	return ret;
}