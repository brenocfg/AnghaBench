#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_1__* constraints; int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl2_reg; } ;
struct TYPE_3__ {int ramp_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  LP87565_BUCK_CTRL_2_SLEW_RATE ; 
 unsigned int __ffs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int* lp87565_buck_ramp_delay ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_2__* regulators ; 

__attribute__((used)) static int lp87565_buck_set_ramp_delay(struct regulator_dev *rdev,
				       int ramp_delay)
{
	int id = rdev_get_id(rdev);
	unsigned int reg;
	int ret;

	if (ramp_delay <= 470)
		reg = 7;
	else if (ramp_delay <= 940)
		reg = 6;
	else if (ramp_delay <= 1900)
		reg = 5;
	else if (ramp_delay <= 3800)
		reg = 4;
	else if (ramp_delay <= 7500)
		reg = 3;
	else if (ramp_delay <= 10000)
		reg = 2;
	else if (ramp_delay <= 15000)
		reg = 1;
	else
		reg = 0;

	ret = regmap_update_bits(rdev->regmap, regulators[id].ctrl2_reg,
				 LP87565_BUCK_CTRL_2_SLEW_RATE,
				 reg << __ffs(LP87565_BUCK_CTRL_2_SLEW_RATE));
	if (ret) {
		dev_err(&rdev->dev, "SLEW RATE write failed: %d\n", ret);
		return ret;
	}

	rdev->constraints->ramp_delay = lp87565_buck_ramp_delay[reg];

	/* Conservatively give a 15% margin */
	rdev->constraints->ramp_delay =
				rdev->constraints->ramp_delay * 85 / 100;

	return 0;
}