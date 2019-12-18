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
typedef  scalar_t__ u8 ;
struct spmi_regulator {int dummy; } ;
struct regulator_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  spmi_saw_set_vdd ; 
 int spmi_sw_selector_to_hw (struct spmi_regulator*,unsigned int,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
spmi_regulator_saw_set_voltage(struct regulator_dev *rdev, unsigned selector)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	int ret;
	u8 range_sel, voltage_sel;

	ret = spmi_sw_selector_to_hw(vreg, selector, &range_sel, &voltage_sel);
	if (ret)
		return ret;

	if (0 != range_sel) {
		dev_dbg(&rdev->dev, "range_sel = %02X voltage_sel = %02X", \
			range_sel, voltage_sel);
		return -EINVAL;
	}

	/* Always do the SAW register writes on the first CPU */
	return smp_call_function_single(0, spmi_saw_set_vdd, \
					&voltage_sel, true);
}