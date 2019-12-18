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
struct raydium_data {int /*<<< orphan*/  reset_gpio; TYPE_1__* client; int /*<<< orphan*/  avdd; int /*<<< orphan*/  vccio; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RM_POWERON_DELAY_USEC ; 
 int /*<<< orphan*/  RM_RESET_DELAY_MSEC ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raydium_i2c_power_on(struct raydium_data *ts)
{
	int error;

	if (!ts->reset_gpio)
		return 0;

	gpiod_set_value_cansleep(ts->reset_gpio, 1);

	error = regulator_enable(ts->avdd);
	if (error) {
		dev_err(&ts->client->dev,
			"failed to enable avdd regulator: %d\n", error);
		goto release_reset_gpio;
	}

	error = regulator_enable(ts->vccio);
	if (error) {
		regulator_disable(ts->avdd);
		dev_err(&ts->client->dev,
			"failed to enable vccio regulator: %d\n", error);
		goto release_reset_gpio;
	}

	udelay(RM_POWERON_DELAY_USEC);

release_reset_gpio:
	gpiod_set_value_cansleep(ts->reset_gpio, 0);

	if (error)
		return error;

	msleep(RM_RESET_DELAY_MSEC);

	return 0;
}