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
struct elants_data {int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  vcc33; TYPE_1__* client; int /*<<< orphan*/  vccio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ELAN_POWERON_DELAY_USEC ; 
 int /*<<< orphan*/  ELAN_RESET_DELAY_MSEC ; 
 scalar_t__ IS_ERR_OR_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elants_i2c_power_on(struct elants_data *ts)
{
	int error;

	/*
	 * If we do not have reset gpio assume platform firmware
	 * controls regulators and does power them on for us.
	 */
	if (IS_ERR_OR_NULL(ts->reset_gpio))
		return 0;

	gpiod_set_value_cansleep(ts->reset_gpio, 1);

	error = regulator_enable(ts->vcc33);
	if (error) {
		dev_err(&ts->client->dev,
			"failed to enable vcc33 regulator: %d\n",
			error);
		goto release_reset_gpio;
	}

	error = regulator_enable(ts->vccio);
	if (error) {
		dev_err(&ts->client->dev,
			"failed to enable vccio regulator: %d\n",
			error);
		regulator_disable(ts->vcc33);
		goto release_reset_gpio;
	}

	/*
	 * We need to wait a bit after powering on controller before
	 * we are allowed to release reset GPIO.
	 */
	udelay(ELAN_POWERON_DELAY_USEC);

release_reset_gpio:
	gpiod_set_value_cansleep(ts->reset_gpio, 0);
	if (error)
		return error;

	msleep(ELAN_RESET_DELAY_MSEC);

	return 0;
}