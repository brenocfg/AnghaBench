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
struct tda10071_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct tda10071_cmd {int len; scalar_t__* args; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct tda10071_dev* demodulator_priv; } ;
struct dvb_diseqc_slave_reply {unsigned int msg_len; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 scalar_t__ CMD_LNB_UPDATE_REPLY ; 
 int EFAULT ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int tda10071_cmd_execute (struct tda10071_dev*,struct tda10071_cmd*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tda10071_diseqc_recv_slave_reply(struct dvb_frontend *fe,
	struct dvb_diseqc_slave_reply *reply)
{
	struct tda10071_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct tda10071_cmd cmd;
	int ret, i;
	unsigned int uitmp;

	if (!dev->warm) {
		ret = -EFAULT;
		goto error;
	}

	dev_dbg(&client->dev, "\n");

	/* wait LNB RX */
	for (i = 500, uitmp = 0; i && !uitmp; i--) {
		ret = regmap_read(dev->regmap, 0x47, &uitmp);
		if (ret)
			goto error;
		uitmp = (uitmp >> 1) & 1;
		usleep_range(10000, 20000);
	}

	dev_dbg(&client->dev, "loop=%d\n", i);

	if (i == 0) {
		ret = -ETIMEDOUT;
		goto error;
	}

	/* reply len */
	ret = regmap_read(dev->regmap, 0x46, &uitmp);
	if (ret)
		goto error;

	reply->msg_len = uitmp & 0x1f; /* [4:0] */
	if (reply->msg_len > sizeof(reply->msg))
		reply->msg_len = sizeof(reply->msg); /* truncate API max */

	/* read reply */
	cmd.args[0] = CMD_LNB_UPDATE_REPLY;
	cmd.args[1] = 0;
	cmd.len = 2;
	ret = tda10071_cmd_execute(dev, &cmd);
	if (ret)
		goto error;

	ret = regmap_bulk_read(dev->regmap, cmd.len, reply->msg,
			       reply->msg_len);
	if (ret)
		goto error;

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}