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
struct TYPE_4__ {int /*<<< orphan*/  adap; } ;
struct tda8290_priv {int ver; TYPE_1__ i2c_props; int /*<<< orphan*/  tda827x_addr; } ;
struct i2c_msg {unsigned char* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct TYPE_6__ {TYPE_2__ analog_ops; } ;
struct dvb_frontend {TYPE_3__ ops; struct tda8290_priv* analog_demod_priv; } ;

/* Variables and functions */
 int TDA8275A ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 
 int /*<<< orphan*/  stub2 (struct dvb_frontend*,int) ; 

__attribute__((used)) static void tda8290_init_tuner(struct dvb_frontend *fe)
{
	struct tda8290_priv *priv = fe->analog_demod_priv;
	static unsigned char tda8275_init[]  =
		{ 0x00, 0x00, 0x00, 0x40, 0xdC, 0x04, 0xAf,
		  0x3F, 0x2A, 0x04, 0xFF, 0x00, 0x00, 0x40 };
	static unsigned char tda8275a_init[] =
		 { 0x00, 0x00, 0x00, 0x00, 0xdC, 0x05, 0x8b,
		   0x0c, 0x04, 0x20, 0xFF, 0x00, 0x00, 0x4b };
	struct i2c_msg msg = {.addr = priv->tda827x_addr, .flags=0,
			      .buf=tda8275_init, .len = 14};
	if (priv->ver & TDA8275A)
		msg.buf = tda8275a_init;

	if (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(priv->i2c_props.adap, &msg, 1);
	if (fe->ops.analog_ops.i2c_gate_ctrl)
		fe->ops.analog_ops.i2c_gate_ctrl(fe, 0);
}