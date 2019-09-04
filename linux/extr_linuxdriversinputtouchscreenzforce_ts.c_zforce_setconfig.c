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
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int COMMAND_SETCONFIG ; 
 int FRAME_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char) ; 
 int zforce_send_wait (struct zforce_ts*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zforce_setconfig(struct zforce_ts *ts, char b1)
{
	struct i2c_client *client = ts->client;
	char buf[7] = { FRAME_START, 5, COMMAND_SETCONFIG,
			b1, 0, 0, 0 };

	dev_dbg(&client->dev, "set config to (%d)\n", b1);

	return zforce_send_wait(ts, &buf[0], ARRAY_SIZE(buf));
}