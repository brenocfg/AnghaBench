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
struct tda10071_dev {int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct tda10071_cmd {int* args; int len; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct tda10071_dev* demodulator_priv; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;

/* Variables and functions */
 int CMD_LNB_SET_DC_LEVEL ; 
 int EFAULT ; 
 int EINVAL ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int tda10071_cmd_execute (struct tda10071_dev*,struct tda10071_cmd*) ; 

__attribute__((used)) static int tda10071_set_voltage(struct dvb_frontend *fe,
	enum fe_sec_voltage fe_sec_voltage)
{
	struct tda10071_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	struct tda10071_cmd cmd;
	int ret;
	u8 voltage;

	if (!dev->warm) {
		ret = -EFAULT;
		goto error;
	}

	dev_dbg(&client->dev, "voltage=%d\n", fe_sec_voltage);

	switch (fe_sec_voltage) {
	case SEC_VOLTAGE_13:
		voltage = 0;
		break;
	case SEC_VOLTAGE_18:
		voltage = 1;
		break;
	case SEC_VOLTAGE_OFF:
		voltage = 0;
		break;
	default:
		dev_dbg(&client->dev, "invalid fe_sec_voltage\n");
		ret = -EINVAL;
		goto error;
	}

	cmd.args[0] = CMD_LNB_SET_DC_LEVEL;
	cmd.args[1] = 0;
	cmd.args[2] = voltage;
	cmd.len = 3;
	ret = tda10071_cmd_execute(dev, &cmd);
	if (ret)
		goto error;

	return ret;
error:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}