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
typedef  int u8 ;
struct tda10071_dev {int /*<<< orphan*/  regmap; int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct tda10071_cmd {int* args; int len; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct tda10071_dev* demodulator_priv; } ;
typedef  enum fe_sec_mini_cmd { ____Placeholder_fe_sec_mini_cmd } fe_sec_mini_cmd ;

/* Variables and functions */
 int CMD_LNB_SEND_TONEBURST ; 
 int EFAULT ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
#define  SEC_MINI_A 129 
#define  SEC_MINI_B 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int regmap_read (int /*<<< orphan*/ ,int,unsigned int*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int,int) ; 
 int tda10071_cmd_execute (struct tda10071_dev*,struct tda10071_cmd*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int tda10071_diseqc_send_burst(struct dvb_frontend *fe,
	enum fe_sec_mini_cmd fe_sec_mini_cmd)
{
	struct tda10071_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct tda10071_cmd cmd;
	int ret, i;
	unsigned int uitmp;
	u8 burst;

	if (!dev->warm) {
		ret = -EFAULT;
		goto error;
	}

	dev_dbg(&client->dev, "fe_sec_mini_cmd=%d\n", fe_sec_mini_cmd);

	switch (fe_sec_mini_cmd) {
	case SEC_MINI_A:
		burst = 0;
		break;
	case SEC_MINI_B:
		burst = 1;
		break;
	default:
		dev_dbg(&client->dev, "invalid fe_sec_mini_cmd\n");
		ret = -EINVAL;
		goto error;
	}

	/* wait LNB TX */
	for (i = 500, uitmp = 0; i && !uitmp; i--) {
		ret = regmap_read(dev->regmap, 0x47, &uitmp);
		if (ret)
			goto error;
		uitmp = (uitmp >> 0) & 1;
		usleep_range(10000, 20000);
	}

	dev_dbg(&client->dev, "loop=%d\n", i);

	if (i == 0) {
		ret = -ETIMEDOUT;
		goto error;
	}

	ret = regmap_update_bits(dev->regmap, 0x47, 0x01, 0x00);
	if (ret)
		goto error;

	cmd.args[0] = CMD_LNB_SEND_TONEBURST;
	cmd.args[1] = 0;
	cmd.args[2] = burst;
	cmd.len = 3;
	ret = tda10071_cmd_execute(dev, &cmd);
	if (ret)
		goto error;

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}