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
struct regulator_dev {int /*<<< orphan*/  desc; } ;

/* Variables and functions */
 int regulator_desc_list_voltage_linear_range (int /*<<< orphan*/ ,unsigned int) ; 

int regulator_list_voltage_linear_range(struct regulator_dev *rdev,
					unsigned int selector)
{
	return regulator_desc_list_voltage_linear_range(rdev->desc, selector);
}