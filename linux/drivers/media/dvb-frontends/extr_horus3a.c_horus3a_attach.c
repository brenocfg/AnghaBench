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
typedef  int u8 ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct horus3a_priv {int i2c_address; struct i2c_adapter* i2c; int /*<<< orphan*/  set_tuner; int /*<<< orphan*/  set_tuner_data; } ;
struct horus3a_config {int i2c_address; int xtal_freq_mhz; int /*<<< orphan*/  set_tuner_callback; int /*<<< orphan*/  set_tuner_priv; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {struct horus3a_priv* tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,struct i2c_adapter*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  horus3a_enter_power_save (struct horus3a_priv*) ; 
 int /*<<< orphan*/  horus3a_tuner_ops ; 
 int /*<<< orphan*/  horus3a_write_reg (struct horus3a_priv*,int,int) ; 
 int /*<<< orphan*/  horus3a_write_regs (struct horus3a_priv*,int,int*,int) ; 
 struct horus3a_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

struct dvb_frontend *horus3a_attach(struct dvb_frontend *fe,
				    const struct horus3a_config *config,
				    struct i2c_adapter *i2c)
{
	u8 buf[3], val;
	struct horus3a_priv *priv = NULL;

	priv = kzalloc(sizeof(struct horus3a_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;
	priv->i2c_address = (config->i2c_address >> 1);
	priv->i2c = i2c;
	priv->set_tuner_data = config->set_tuner_priv;
	priv->set_tuner = config->set_tuner_callback;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);

	/* wait 4ms after power on */
	usleep_range(4000, 6000);
	/* IQ Generator disable */
	horus3a_write_reg(priv, 0x2a, 0x79);
	/* REF_R = Xtal Frequency */
	buf[0] = config->xtal_freq_mhz;
	buf[1] = config->xtal_freq_mhz;
	buf[2] = 0;
	/* 0x6 - 0x8 */
	horus3a_write_regs(priv, 0x6, buf, 3);
	/* IQ Out = Single Ended */
	horus3a_write_reg(priv, 0x0a, 0x40);
	switch (config->xtal_freq_mhz) {
	case 27:
		val = 0x1f;
		break;
	case 24:
		val = 0x10;
		break;
	case 16:
		val = 0xc;
		break;
	default:
		val = 0;
		dev_warn(&priv->i2c->dev,
			"horus3a: invalid xtal frequency %dMHz\n",
			config->xtal_freq_mhz);
		break;
	}
	val <<= 2;
	horus3a_write_reg(priv, 0x0e, val);
	horus3a_enter_power_save(priv);
	usleep_range(3000, 5000);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	memcpy(&fe->ops.tuner_ops, &horus3a_tuner_ops,
				sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = priv;
	dev_info(&priv->i2c->dev,
		"Sony HORUS3A attached on addr=%x at I2C adapter %p\n",
		priv->i2c_address, priv->i2c);
	return fe;
}