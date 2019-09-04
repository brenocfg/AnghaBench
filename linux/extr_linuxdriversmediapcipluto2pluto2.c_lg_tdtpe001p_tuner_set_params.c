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
typedef  int u32 ;
struct pluto {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int* buf; int len; scalar_t__ flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; int bandwidth_hz; } ;
struct dvb_frontend {TYPE_1__ ops; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EREMOTEIO ; 
 int I2C_ADDR_TUA6034 ; 
 int divide (int,int) ; 
 struct pluto* frontend_to_pluto (struct dvb_frontend*) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int lg_tdtpe001p_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct pluto *pluto = frontend_to_pluto(fe);
	struct i2c_msg msg;
	int ret;
	u8 buf[4];
	u32 div;

	// Fref = 166.667 Hz
	// Fref * 3 = 500.000 Hz
	// IF = 36166667
	// IF / Fref = 217
	//div = divide(p->frequency + 36166667, 166667);
	div = divide(p->frequency * 3, 500000) + 217;
	buf[0] = (div >> 8) & 0x7f;
	buf[1] = (div >> 0) & 0xff;

	if (p->frequency < 611000000)
		buf[2] = 0xb4;
	else if (p->frequency < 811000000)
		buf[2] = 0xbc;
	else
		buf[2] = 0xf4;

	// VHF: 174-230 MHz
	// center: 350 MHz
	// UHF: 470-862 MHz
	if (p->frequency < 350000000)
		buf[3] = 0x02;
	else
		buf[3] = 0x04;

	if (p->bandwidth_hz == 8000000)
		buf[3] |= 0x08;

	msg.addr = I2C_ADDR_TUA6034 >> 1;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = sizeof(buf);

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	ret = i2c_transfer(&pluto->i2c_adap, &msg, 1);
	if (ret < 0)
		return ret;
	else if (ret == 0)
		return -EREMOTEIO;

	return 0;
}