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
typedef  int /*<<< orphan*/  u8 ;
struct lnbh29_priv {TYPE_1__* i2c; int /*<<< orphan*/ * config; int /*<<< orphan*/  i2c_address; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_frontend {struct lnbh29_priv* sec_priv; } ;
typedef  enum fe_sec_voltage { ____Placeholder_fe_sec_voltage } fe_sec_voltage ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  LNBH29_VSEL_0 ; 
 int /*<<< orphan*/  LNBH29_VSEL_13 ; 
 int /*<<< orphan*/  LNBH29_VSEL_18 ; 
 int /*<<< orphan*/  LNBH29_VSEL_MASK ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int i2c_transfer (TYPE_1__*,struct i2c_msg*,int) ; 
 int lnbh29_read_vmon (struct lnbh29_priv*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int lnbh29_set_voltage(struct dvb_frontend *fe,
			      enum fe_sec_voltage voltage)
{
	struct lnbh29_priv *priv = fe->sec_priv;
	u8 data_reg;
	int ret;
	struct i2c_msg msg = {
		.addr = priv->i2c_address,
		.flags = 0,
		.len = sizeof(priv->config),
		.buf = priv->config
	};

	switch (voltage) {
	case SEC_VOLTAGE_OFF:
		data_reg = LNBH29_VSEL_0;
		break;
	case SEC_VOLTAGE_13:
		data_reg = LNBH29_VSEL_13;
		break;
	case SEC_VOLTAGE_18:
		data_reg = LNBH29_VSEL_18;
		break;
	default:
		return -EINVAL;
	}
	priv->config[1] &= ~LNBH29_VSEL_MASK;
	priv->config[1] |= data_reg;

	ret = i2c_transfer(priv->i2c, &msg, 1);
	if (ret >= 0 && ret != 1)
		ret = -EIO;
	if (ret < 0) {
		dev_err(&priv->i2c->dev, "LNBH29 I2C transfer error (%d)\n",
			ret);
		return ret;
	}

	/* Soft-start time (Vout 0V to 18V) is Typ. 6ms. */
	usleep_range(6000, 20000);

	if (voltage == SEC_VOLTAGE_OFF)
		return 0;

	return lnbh29_read_vmon(priv);
}