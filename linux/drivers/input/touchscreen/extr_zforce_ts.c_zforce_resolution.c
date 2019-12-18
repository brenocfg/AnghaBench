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
typedef  int u16 ;
struct zforce_ts {struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int COMMAND_RESOLUTION ; 
 int FRAME_START ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,int) ; 
 int zforce_send_wait (struct zforce_ts*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zforce_resolution(struct zforce_ts *ts, u16 x, u16 y)
{
	struct i2c_client *client = ts->client;
	char buf[7] = { FRAME_START, 5, COMMAND_RESOLUTION,
			(x & 0xff), ((x >> 8) & 0xff),
			(y & 0xff), ((y >> 8) & 0xff) };

	dev_dbg(&client->dev, "set resolution to (%d,%d)\n", x, y);

	return zforce_send_wait(ts, &buf[0], ARRAY_SIZE(buf));
}