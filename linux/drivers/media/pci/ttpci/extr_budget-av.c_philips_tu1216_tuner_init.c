#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  tu1216_init ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; } ;
struct budget {int /*<<< orphan*/  i2c_adap; } ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int philips_tu1216_tuner_init(struct dvb_frontend *fe)
{
	struct budget *budget = (struct budget *) fe->dvb->priv;
	static u8 tu1216_init[] = { 0x0b, 0xf5, 0x85, 0xab };
	struct i2c_msg tuner_msg = {.addr = 0x60,.flags = 0,.buf = tu1216_init,.len = sizeof(tu1216_init) };

	// setup PLL configuration
	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&budget->i2c_adap, &tuner_msg, 1) != 1)
		return -EIO;
	msleep(1);

	return 0;
}