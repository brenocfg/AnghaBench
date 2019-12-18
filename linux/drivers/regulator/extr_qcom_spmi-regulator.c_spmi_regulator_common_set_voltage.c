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
struct spmi_regulator {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_COMMON_REG_VOLTAGE_RANGE ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int spmi_sw_selector_to_hw (struct spmi_regulator*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int spmi_vreg_write (struct spmi_regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
spmi_regulator_common_set_voltage(struct regulator_dev *rdev, unsigned selector)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	int ret;
	u8 buf[2];
	u8 range_sel, voltage_sel;

	ret = spmi_sw_selector_to_hw(vreg, selector, &range_sel, &voltage_sel);
	if (ret)
		return ret;

	buf[0] = range_sel;
	buf[1] = voltage_sel;
	return spmi_vreg_write(vreg, SPMI_COMMON_REG_VOLTAGE_RANGE, buf, 2);
}