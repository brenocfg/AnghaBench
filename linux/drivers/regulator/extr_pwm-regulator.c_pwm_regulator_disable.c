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
struct pwm_regulator_data {int /*<<< orphan*/  enb_gpio; int /*<<< orphan*/  pwm; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pwm_disable (int /*<<< orphan*/ ) ; 
 struct pwm_regulator_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int pwm_regulator_disable(struct regulator_dev *dev)
{
	struct pwm_regulator_data *drvdata = rdev_get_drvdata(dev);

	pwm_disable(drvdata->pwm);

	gpiod_set_value_cansleep(drvdata->enb_gpio, 0);

	return 0;
}