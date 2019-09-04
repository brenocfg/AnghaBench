#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct zet6223_ts {TYPE_2__* supplies; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_6__ {char* supply; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  ZET6223_POWER_ON_DELAY_MSEC ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct zet6223_ts*) ; 
 int devm_regulator_bulk_get (struct device*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int regulator_bulk_enable (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zet6223_power_off ; 

__attribute__((used)) static int zet6223_power_on(struct zet6223_ts *ts)
{
	struct device *dev = &ts->client->dev;
	int error;

	ts->supplies[0].supply = "vio";
	ts->supplies[1].supply = "vcc";

	error = devm_regulator_bulk_get(dev, ARRAY_SIZE(ts->supplies),
					ts->supplies);
	if (error)
		return error;

	error = regulator_bulk_enable(ARRAY_SIZE(ts->supplies), ts->supplies);
	if (error)
		return error;

	msleep(ZET6223_POWER_ON_DELAY_MSEC);

	error = devm_add_action_or_reset(dev, zet6223_power_off, ts);
	if (error) {
		dev_err(dev, "failed to install poweroff action: %d\n", error);
		return error;
	}

	return 0;
}