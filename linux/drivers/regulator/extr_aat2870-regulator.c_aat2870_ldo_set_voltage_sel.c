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
struct aat2870_regulator {unsigned int voltage_shift; int /*<<< orphan*/  voltage_mask; int /*<<< orphan*/  voltage_addr; struct aat2870_data* aat2870; } ;
struct aat2870_data {int (* update ) (struct aat2870_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 struct aat2870_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int stub1 (struct aat2870_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int aat2870_ldo_set_voltage_sel(struct regulator_dev *rdev,
				       unsigned selector)
{
	struct aat2870_regulator *ri = rdev_get_drvdata(rdev);
	struct aat2870_data *aat2870 = ri->aat2870;

	return aat2870->update(aat2870, ri->voltage_addr, ri->voltage_mask,
			       selector << ri->voltage_shift);
}