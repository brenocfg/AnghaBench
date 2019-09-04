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
struct zforce_ts {char command_waiting; int command_result; int /*<<< orphan*/  command_mutex; int /*<<< orphan*/  command_done; int /*<<< orphan*/  access_mutex; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETIME ; 
 int /*<<< orphan*/  WAIT_TIMEOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int i2c_master_send (struct i2c_client*,char const*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zforce_send_wait(struct zforce_ts *ts, const char *buf, int len)
{
	struct i2c_client *client = ts->client;
	int ret;

	ret = mutex_trylock(&ts->command_mutex);
	if (!ret) {
		dev_err(&client->dev, "already waiting for a command\n");
		return -EBUSY;
	}

	dev_dbg(&client->dev, "sending %d bytes for command 0x%x\n",
		buf[1], buf[2]);

	ts->command_waiting = buf[2];

	mutex_lock(&ts->access_mutex);
	ret = i2c_master_send(client, buf, len);
	mutex_unlock(&ts->access_mutex);
	if (ret < 0) {
		dev_err(&client->dev, "i2c send data request error: %d\n", ret);
		goto unlock;
	}

	dev_dbg(&client->dev, "waiting for result for command 0x%x\n", buf[2]);

	if (wait_for_completion_timeout(&ts->command_done, WAIT_TIMEOUT) == 0) {
		ret = -ETIME;
		goto unlock;
	}

	ret = ts->command_result;

unlock:
	mutex_unlock(&ts->command_mutex);
	return ret;
}