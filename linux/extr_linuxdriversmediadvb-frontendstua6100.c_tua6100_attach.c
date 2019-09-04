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
struct tua6100_priv {int i2c_address; struct i2c_adapter* i2c; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_tuner_ops {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuner_ops; int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {struct tua6100_priv* tuner_priv; TYPE_1__ ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 struct tua6100_priv* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  tua6100_tuner_ops ; 

struct dvb_frontend *tua6100_attach(struct dvb_frontend *fe, int addr, struct i2c_adapter *i2c)
{
	struct tua6100_priv *priv = NULL;
	u8 b1 [] = { 0x80 };
	u8 b2 [] = { 0x00 };
	struct i2c_msg msg [] = { { .addr = addr, .flags = 0, .buf = b1, .len = 1 },
				  { .addr = addr, .flags = I2C_M_RD, .buf = b2, .len = 1 } };
	int ret;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer (i2c, msg, 2);
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 0);

	if (ret != 2)
		return NULL;

	priv = kzalloc(sizeof(struct tua6100_priv), GFP_KERNEL);
	if (priv == NULL)
		return NULL;

	priv->i2c_address = addr;
	priv->i2c = i2c;

	memcpy(&fe->ops.tuner_ops, &tua6100_tuner_ops, sizeof(struct dvb_tuner_ops));
	fe->tuner_priv = priv;
	return fe;
}