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
typedef  int /*<<< orphan*/  u8 ;
struct spmi_voltage_range {int range_sel; } ;
struct spmi_regulator {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SPMI_COMMON_REG_VOLTAGE_SET ; 
 int /*<<< orphan*/  ULT_SMPS_RANGE_SPLIT ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int spmi_hw_selector_to_sw (struct spmi_regulator*,int /*<<< orphan*/ ,struct spmi_voltage_range const*) ; 
 struct spmi_voltage_range* spmi_regulator_find_range (struct spmi_regulator*) ; 
 int /*<<< orphan*/  spmi_vreg_read (struct spmi_regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int spmi_regulator_ult_lo_smps_get_voltage(struct regulator_dev *rdev)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	const struct spmi_voltage_range *range;
	u8 voltage_sel;

	spmi_vreg_read(vreg, SPMI_COMMON_REG_VOLTAGE_SET, &voltage_sel, 1);

	range = spmi_regulator_find_range(vreg);
	if (!range)
		return -EINVAL;

	if (range->range_sel == 1)
		voltage_sel &= ~ULT_SMPS_RANGE_SPLIT;

	return spmi_hw_selector_to_sw(vreg, voltage_sel, range);
}