#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct m88ds3103_dev {TYPE_1__* cfg; int /*<<< orphan*/  warm; struct i2c_client* client; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct m88ds3103_dev* demodulator_priv; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_2__ {int lnb_hv_pol; int lnb_en_pol; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int m88ds3103_update_bits (struct m88ds3103_dev*,int,int,unsigned int) ; 

__attribute__((used)) static int m88ds3103_set_voltage(struct dvb_frontend *fe,
	enum fe_sec_voltage fe_sec_voltage)
{
	struct m88ds3103_dev *dev = fe->demodulator_priv;
	struct i2c_client *client = dev->client;
	int ret;
	unsigned int utmp;
	bool voltage_sel, voltage_dis;

	dev_dbg(&client->dev, "fe_sec_voltage=%d\n", fe_sec_voltage);

	if (!dev->warm) {
		ret = -EAGAIN;
		goto err;
	}

	switch (fe_sec_voltage) {
	case SEC_VOLTAGE_18:
		voltage_sel = true;
		voltage_dis = false;
		break;
	case SEC_VOLTAGE_13:
		voltage_sel = false;
		voltage_dis = false;
		break;
	case SEC_VOLTAGE_OFF:
		voltage_sel = false;
		voltage_dis = true;
		break;
	default:
		dev_dbg(&client->dev, "invalid fe_sec_voltage\n");
		ret = -EINVAL;
		goto err;
	}

	/* output pin polarity */
	voltage_sel ^= dev->cfg->lnb_hv_pol;
	voltage_dis ^= dev->cfg->lnb_en_pol;

	utmp = voltage_dis << 1 | voltage_sel << 0;
	ret = m88ds3103_update_bits(dev, 0xa2, 0x03, utmp);
	if (ret)
		goto err;

	return 0;
err:
	dev_dbg(&client->dev, "failed=%d\n", ret);
	return ret;
}