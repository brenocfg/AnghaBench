#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  tu1216_init ;
struct tda1004x_state {TYPE_3__* config; } ;
struct saa7134_dev {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_1__ ops; struct tda1004x_state* demodulator_priv; TYPE_2__* dvb; } ;
struct TYPE_6__ {int tuner_address; } ;
struct TYPE_5__ {struct saa7134_dev* priv; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int philips_tu1216_init(struct dvb_frontend *fe)
{
	struct saa7134_dev *dev = fe->dvb->priv;
	struct tda1004x_state *state = fe->demodulator_priv;
	u8 addr = state->config->tuner_address;
	static u8 tu1216_init[] = { 0x0b, 0xf5, 0x85, 0xab };
	struct i2c_msg tuner_msg = {.addr = addr,.flags = 0,.buf = tu1216_init,.len = sizeof(tu1216_init) };

	/* setup PLL configuration */
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&dev->i2c_adap, &tuner_msg, 1) != 1)
		return -EIO;
	msleep(1);

	return 0;
}