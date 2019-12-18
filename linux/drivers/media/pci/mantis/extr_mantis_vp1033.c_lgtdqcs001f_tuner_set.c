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
struct i2c_adapter {int dummy; } ;
struct mantis_pci {struct i2c_adapter adapter; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dtv_frontend_properties {int frequency; } ;
struct dvb_frontend {TYPE_1__* dvb; struct dtv_frontend_properties dtv_property_cache; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {struct mantis_pci* priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 

__attribute__((used)) static int lgtdqcs001f_tuner_set(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;
	struct mantis_pci *mantis	= fe->dvb->priv;
	struct i2c_adapter *adapter	= &mantis->adapter;

	u8 buf[4];
	u32 div;


	struct i2c_msg msg = {.addr = 0x61, .flags = 0, .buf = buf, .len = sizeof(buf)};

	div = p->frequency / 250;

	buf[0] = (div >> 8) & 0x7f;
	buf[1] =  div & 0xff;
	buf[2] =  0x83;
	buf[3] =  0xc0;

	if (p->frequency < 1531000)
		buf[3] |= 0x04;
	else
		buf[3] &= ~0x04;
	if (i2c_transfer(adapter, &msg, 1) < 0) {
		dprintk(MANTIS_ERROR, 1, "Write: I2C Transfer failed");
		return -EIO;
	}
	msleep_interruptible(100);

	return 0;
}