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
typedef  int u8 ;
struct spmi_voltage_range {int step_uV; } ;
struct spmi_regulator {int /*<<< orphan*/  slew_rate; int /*<<< orphan*/  dev; TYPE_1__* set_points; } ;
struct TYPE_2__ {struct spmi_voltage_range* range; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_COMMON_REG_STEP_CTRL ; 
 int SPMI_FTSMPS426_STEP_CTRL_DELAY_MASK ; 
 int SPMI_FTSMPS426_STEP_CTRL_DELAY_SHIFT ; 
 int SPMI_FTSMPS426_STEP_DELAY ; 
 int SPMI_FTSMPS426_STEP_MARGIN_DEN ; 
 int SPMI_FTSMPS426_STEP_MARGIN_NUM ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  max (int,int) ; 
 int spmi_vreg_read (struct spmi_regulator*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int spmi_regulator_init_slew_rate_ftsmps426(struct spmi_regulator *vreg,
						   int clock_rate)
{
	int ret;
	u8 reg = 0;
	int delay, slew_rate;
	const struct spmi_voltage_range *range = &vreg->set_points->range[0];

	ret = spmi_vreg_read(vreg, SPMI_COMMON_REG_STEP_CTRL, &reg, 1);
	if (ret) {
		dev_err(vreg->dev, "spmi read failed, ret=%d\n", ret);
		return ret;
	}

	delay = reg & SPMI_FTSMPS426_STEP_CTRL_DELAY_MASK;
	delay >>= SPMI_FTSMPS426_STEP_CTRL_DELAY_SHIFT;

	/* slew_rate has units of uV/us */
	slew_rate = clock_rate * range->step_uV;
	slew_rate /= 1000 * (SPMI_FTSMPS426_STEP_DELAY << delay);
	slew_rate *= SPMI_FTSMPS426_STEP_MARGIN_NUM;
	slew_rate /= SPMI_FTSMPS426_STEP_MARGIN_DEN;

	/* Ensure that the slew rate is greater than 0 */
	vreg->slew_rate = max(slew_rate, 1);

	return ret;
}