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
typedef  int u32 ;
struct ttusb {scalar_t__ revision; int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ TTUSB_REV_2_2 ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int philips_tsa5059_tuner_set_params(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct ttusb* ttusb = (struct ttusb*) fe->dvb->priv;
	u8 buf[4];
	u32 div;
	struct i2c_msg msg = {.addr = 0x61,.flags = 0,.buf = buf,.len = sizeof(buf) };

	if ((p->frequency < 950000) || (p->frequency > 2150000))
		return -EINVAL;

	div = (p->frequency + (125 - 1)) / 125;	/* round correctly */
	buf[0] = (div >> 8) & 0x7f;
	buf[1] = div & 0xff;
	buf[2] = 0x80 | ((div & 0x18000) >> 10) | 4;
	buf[3] = 0xC4;

	if (p->frequency > 1530000)
		buf[3] = 0xC0;

	/* BSBE1 wants XCE bit set */
	if (ttusb->revision == TTUSB_REV_2_2)
		buf[3] |= 0x20;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	if (i2c_transfer(&ttusb->i2c_adap, &msg, 1) != 1)
		return -EIO;

	return 0;
}