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
struct zforce_ts {int command_waiting; int command_result; int /*<<< orphan*/  command_done; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static void zforce_complete(struct zforce_ts *ts, int cmd, int result)
{
	struct i2c_client *client = ts->client;

	if (ts->command_waiting == cmd) {
		dev_dbg(&client->dev, "completing command 0x%x\n", cmd);
		ts->command_result = result;
		complete(&ts->command_done);
	} else {
		dev_dbg(&client->dev, "command %d not for us\n", cmd);
	}
}