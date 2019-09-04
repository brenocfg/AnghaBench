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
struct zforce_ts_platdata {int /*<<< orphan*/  y_max; int /*<<< orphan*/  x_max; } ;
struct zforce_ts {struct zforce_ts_platdata* pdata; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_DATAREQUEST ; 
 int /*<<< orphan*/  COMMAND_DEACTIVATE ; 
 int /*<<< orphan*/  COMMAND_INITIALIZE ; 
 int /*<<< orphan*/  SETCONFIG_DUALTOUCH ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int zforce_command (struct zforce_ts*,int /*<<< orphan*/ ) ; 
 int zforce_command_wait (struct zforce_ts*,int /*<<< orphan*/ ) ; 
 int zforce_resolution (struct zforce_ts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zforce_scan_frequency (struct zforce_ts*,int,int,int) ; 
 int zforce_setconfig (struct zforce_ts*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zforce_start(struct zforce_ts *ts)
{
	struct i2c_client *client = ts->client;
	const struct zforce_ts_platdata *pdata = ts->pdata;
	int ret;

	dev_dbg(&client->dev, "starting device\n");

	ret = zforce_command_wait(ts, COMMAND_INITIALIZE);
	if (ret) {
		dev_err(&client->dev, "Unable to initialize, %d\n", ret);
		return ret;
	}

	ret = zforce_resolution(ts, pdata->x_max, pdata->y_max);
	if (ret) {
		dev_err(&client->dev, "Unable to set resolution, %d\n", ret);
		goto error;
	}

	ret = zforce_scan_frequency(ts, 10, 50, 50);
	if (ret) {
		dev_err(&client->dev, "Unable to set scan frequency, %d\n",
			ret);
		goto error;
	}

	ret = zforce_setconfig(ts, SETCONFIG_DUALTOUCH);
	if (ret) {
		dev_err(&client->dev, "Unable to set config\n");
		goto error;
	}

	/* start sending touch events */
	ret = zforce_command(ts, COMMAND_DATAREQUEST);
	if (ret) {
		dev_err(&client->dev, "Unable to request data\n");
		goto error;
	}

	/*
	 * Per NN, initial cal. take max. of 200msec.
	 * Allow time to complete this calibration
	 */
	msleep(200);

	return 0;

error:
	zforce_command_wait(ts, COMMAND_DEACTIVATE);
	return ret;
}