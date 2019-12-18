#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int dutycycle_unit; int min_uV_dutycycle; int max_uV_dutycycle; } ;
struct TYPE_4__ {int continuous_voltage_range; int /*<<< orphan*/ * ops; } ;
struct pwm_regulator_data {TYPE_3__ continuous; TYPE_1__ desc; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_2__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  of_property_read_u32 (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  of_property_read_u32_array (int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  pwm_regulator_voltage_continuous_ops ; 

__attribute__((used)) static int pwm_regulator_init_continuous(struct platform_device *pdev,
					 struct pwm_regulator_data *drvdata)
{
	u32 dutycycle_range[2] = { 0, 100 };
	u32 dutycycle_unit = 100;

	drvdata->desc.ops = &pwm_regulator_voltage_continuous_ops;
	drvdata->desc.continuous_voltage_range = true;

	of_property_read_u32_array(pdev->dev.of_node,
				   "pwm-dutycycle-range",
				   dutycycle_range, 2);
	of_property_read_u32(pdev->dev.of_node, "pwm-dutycycle-unit",
			     &dutycycle_unit);

	if (dutycycle_range[0] > dutycycle_unit ||
	    dutycycle_range[1] > dutycycle_unit)
		return -EINVAL;

	drvdata->continuous.dutycycle_unit = dutycycle_unit;
	drvdata->continuous.min_uV_dutycycle = dutycycle_range[0];
	drvdata->continuous.max_uV_dutycycle = dutycycle_range[1];

	return 0;
}