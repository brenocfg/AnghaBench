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
struct zforce_ts {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_DEACTIVATE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int zforce_command_wait (struct zforce_ts*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zforce_stop(struct zforce_ts *ts)
{
	struct i2c_client *client = ts->client;
	int ret;

	dev_dbg(&client->dev, "stopping device\n");

	/* Deactivates touch sensing and puts the device into sleep. */
	ret = zforce_command_wait(ts, COMMAND_DEACTIVATE);
	if (ret != 0) {
		dev_err(&client->dev, "could not deactivate device, %d\n",
			ret);
		return ret;
	}

	return 0;
}