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
struct bq2415x_device {int mode; TYPE_2__* charger; int /*<<< orphan*/  dev; } ;
typedef  enum bq2415x_mode { ____Placeholder_bq2415x_mode } bq2415x_mode ;
struct TYPE_3__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BQ2415X_BOOST_MODE_DISABLE ; 
 int /*<<< orphan*/  BQ2415X_BOOST_MODE_ENABLE ; 
 int /*<<< orphan*/  BQ2415X_CHARGER_DISABLE ; 
 int /*<<< orphan*/  BQ2415X_CHARGER_ENABLE ; 
#define  BQ2415X_MODE_BOOST 132 
#define  BQ2415X_MODE_DEDICATED_CHARGER 131 
#define  BQ2415X_MODE_HOST_CHARGER 130 
#define  BQ2415X_MODE_NONE 129 
#define  BQ2415X_MODE_OFF 128 
 int /*<<< orphan*/  battery_regulation_voltage ; 
 int bq2415x_exec_command (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 int bq2415x_set_current_limit (struct bq2415x_device*,int) ; 
 int /*<<< orphan*/  bq2415x_set_default_value (struct bq2415x_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sysfs_notify (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  weak_battery_voltage ; 

__attribute__((used)) static int bq2415x_set_mode(struct bq2415x_device *bq, enum bq2415x_mode mode)
{
	int ret = 0;
	int charger = 0;
	int boost = 0;

	if (mode == BQ2415X_MODE_BOOST)
		boost = 1;
	else if (mode != BQ2415X_MODE_OFF)
		charger = 1;

	if (!charger)
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGER_DISABLE);

	if (!boost)
		ret = bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_DISABLE);

	if (ret < 0)
		return ret;

	switch (mode) {
	case BQ2415X_MODE_OFF:
		dev_dbg(bq->dev, "changing mode to: Offline\n");
		ret = bq2415x_set_current_limit(bq, 100);
		break;
	case BQ2415X_MODE_NONE:
		dev_dbg(bq->dev, "changing mode to: N/A\n");
		ret = bq2415x_set_current_limit(bq, 100);
		break;
	case BQ2415X_MODE_HOST_CHARGER:
		dev_dbg(bq->dev, "changing mode to: Host/HUB charger\n");
		ret = bq2415x_set_current_limit(bq, 500);
		break;
	case BQ2415X_MODE_DEDICATED_CHARGER:
		dev_dbg(bq->dev, "changing mode to: Dedicated charger\n");
		ret = bq2415x_set_current_limit(bq, 1800);
		break;
	case BQ2415X_MODE_BOOST: /* Boost mode */
		dev_dbg(bq->dev, "changing mode to: Boost\n");
		ret = bq2415x_set_current_limit(bq, 100);
		break;
	}

	if (ret < 0)
		return ret;

	if (charger)
		ret = bq2415x_exec_command(bq, BQ2415X_CHARGER_ENABLE);
	else if (boost)
		ret = bq2415x_exec_command(bq, BQ2415X_BOOST_MODE_ENABLE);

	if (ret < 0)
		return ret;

	bq2415x_set_default_value(bq, weak_battery_voltage);
	bq2415x_set_default_value(bq, battery_regulation_voltage);

	bq->mode = mode;
	sysfs_notify(&bq->charger->dev.kobj, NULL, "mode");

	return 0;

}