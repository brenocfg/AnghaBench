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
struct tps65132_regulator {int /*<<< orphan*/  dev; struct tps65132_reg_pdata* reg_pdata; } ;
struct tps65132_reg_pdata {int ena_gpio_state; int /*<<< orphan*/  en_gpiod; } ;
struct regulator_dev {TYPE_1__* constraints; } ;
struct TYPE_2__ {scalar_t__ active_discharge; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ REGULATOR_ACTIVE_DISCHARGE_DISABLE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 struct tps65132_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regulator_set_active_discharge_regmap (struct regulator_dev*,int) ; 

__attribute__((used)) static int tps65132_regulator_enable(struct regulator_dev *rdev)
{
	struct tps65132_regulator *tps = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	struct tps65132_reg_pdata *rpdata = &tps->reg_pdata[id];
	int ret;

	if (!IS_ERR(rpdata->en_gpiod)) {
		gpiod_set_value_cansleep(rpdata->en_gpiod, 1);
		rpdata->ena_gpio_state = 1;
	}

	/* Hardware automatically enable discharge bit in enable */
	if (rdev->constraints->active_discharge ==
			REGULATOR_ACTIVE_DISCHARGE_DISABLE) {
		ret = regulator_set_active_discharge_regmap(rdev, false);
		if (ret < 0) {
			dev_err(tps->dev, "Failed to disable active discharge: %d\n",
				ret);
			return ret;
		}
	}

	return 0;
}