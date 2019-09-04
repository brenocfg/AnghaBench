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
struct si2157_dev {int active; int /*<<< orphan*/  stat_work; } ;
struct si2157_cmd {int wlen; int rlen; int /*<<< orphan*/  args; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* tuner_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct si2157_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 int si2157_cmd_execute (struct i2c_client*,struct si2157_cmd*) ; 

__attribute__((used)) static int si2157_sleep(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->tuner_priv;
	struct si2157_dev *dev = i2c_get_clientdata(client);
	int ret;
	struct si2157_cmd cmd;

	dev_dbg(&client->dev, "\n");

	dev->active = false;

	/* stop statistics polling */
	cancel_delayed_work_sync(&dev->stat_work);

	/* standby */
	memcpy(cmd.args, "\x16\x00", 2);
	cmd.wlen = 2;
	cmd.rlen = 1;
	ret = si2157_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}