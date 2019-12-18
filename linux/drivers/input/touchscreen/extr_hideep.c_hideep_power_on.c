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
struct hideep_ts {TYPE_1__* client; int /*<<< orphan*/  reg; scalar_t__ reset_gpio; int /*<<< orphan*/  vcc_vid; int /*<<< orphan*/  vcc_vdd; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIDEEP_RESET_CMD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int hideep_power_on(struct hideep_ts *ts)
{
	int error = 0;

	error = regulator_enable(ts->vcc_vdd);
	if (error)
		dev_err(&ts->client->dev,
			"failed to enable 'vdd' regulator: %d", error);

	usleep_range(999, 1000);

	error = regulator_enable(ts->vcc_vid);
	if (error)
		dev_err(&ts->client->dev,
			"failed to enable 'vcc_vid' regulator: %d",
			error);

	msleep(30);

	if (ts->reset_gpio) {
		gpiod_set_value_cansleep(ts->reset_gpio, 0);
	} else {
		error = regmap_write(ts->reg, HIDEEP_RESET_CMD, 0x01);
		if (error)
			dev_err(&ts->client->dev,
				"failed to send 'reset' command: %d\n", error);
	}

	msleep(50);

	return error;
}