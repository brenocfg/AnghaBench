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
struct regulator_dev {TYPE_1__* desc; } ;
struct TYPE_2__ {int* volt_table; unsigned int n_voltages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINVAL ; 

int regulator_list_voltage_table(struct regulator_dev *rdev,
				 unsigned int selector)
{
	if (!rdev->desc->volt_table) {
		BUG_ON(!rdev->desc->volt_table);
		return -EINVAL;
	}

	if (selector >= rdev->desc->n_voltages)
		return -EINVAL;

	return rdev->desc->volt_table[selector];
}