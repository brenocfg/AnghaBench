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
struct si2168_dev {int active; char version; int warm; } ;
struct si2168_cmd {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct i2c_client* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmd_init (struct si2168_cmd*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 struct si2168_dev* i2c_get_clientdata (struct i2c_client*) ; 
 int si2168_cmd_execute (struct i2c_client*,struct si2168_cmd*) ; 
 int si2168_ts_bus_ctrl (struct dvb_frontend*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si2168_sleep(struct dvb_frontend *fe)
{
	struct i2c_client *client = fe->demodulator_priv;
	struct si2168_dev *dev = i2c_get_clientdata(client);
	int ret;
	struct si2168_cmd cmd;

	dev_dbg(&client->dev, "\n");

	dev->active = false;

	/* tri-state data bus */
	ret = si2168_ts_bus_ctrl(fe, 0);
	if (ret)
		goto err;

	/* Firmware later than B 4.0-11 loses warm state during sleep */
	if (dev->version > ('B' << 24 | 4 << 16 | 0 << 8 | 11 << 0))
		dev->warm = false;

	cmd_init(&cmd, "\x13", 1, 0);
	ret = si2168_cmd_execute(client, &cmd);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}