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
typedef  scalar_t__ u8 ;
struct spmi_voltage_range {int set_point_min_uV; int step_uV; } ;
struct spmi_regulator {TYPE_1__* set_points; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {struct spmi_voltage_range* range; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_FTSMPS426_REG_VOLTAGE_LSB ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  spmi_vreg_read (struct spmi_regulator*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int spmi_regulator_ftsmps426_get_voltage(struct regulator_dev *rdev)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	const struct spmi_voltage_range *range;
	u8 buf[2];
	int uV;

	spmi_vreg_read(vreg, SPMI_FTSMPS426_REG_VOLTAGE_LSB, buf, 2);

	uV = (((unsigned int)buf[1] << 8) | (unsigned int)buf[0]) * 1000;
	range = vreg->set_points->range;

	return (uV - range->set_point_min_uV) / range->step_uV;
}