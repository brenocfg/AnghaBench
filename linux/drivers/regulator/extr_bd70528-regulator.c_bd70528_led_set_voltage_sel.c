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
struct regulator_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int regulator_is_enabled_regmap (struct regulator_dev*) ; 
 int regulator_set_voltage_sel_regmap (struct regulator_dev*,unsigned int) ; 

__attribute__((used)) static int bd70528_led_set_voltage_sel(struct regulator_dev *rdev,
				       unsigned int sel)
{
	int ret;

	ret = regulator_is_enabled_regmap(rdev);
	if (ret < 0)
		return ret;

	if (ret == 0)
		return regulator_set_voltage_sel_regmap(rdev, sel);

	dev_err(&rdev->dev,
		"LED voltage change not allowed when led is enabled\n");

	return -EBUSY;
}