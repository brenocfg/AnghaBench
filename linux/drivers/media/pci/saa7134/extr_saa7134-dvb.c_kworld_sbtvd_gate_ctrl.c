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
struct saa7134_dev {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; unsigned char* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct TYPE_2__ {struct saa7134_dev* priv; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

__attribute__((used)) static int kworld_sbtvd_gate_ctrl(struct dvb_frontend* fe, int enable)
{
	struct saa7134_dev *dev = fe->dvb->priv;

	unsigned char initmsg[] = {0x45, 0x97};
	unsigned char msg_enable[] = {0x45, 0xc1};
	unsigned char msg_disable[] = {0x45, 0x81};
	struct i2c_msg msg = {.addr = 0x4b, .flags = 0, .buf = initmsg, .len = 2};

	if (i2c_transfer(&dev->i2c_adap, &msg, 1) != 1) {
		pr_warn("could not access the I2C gate\n");
		return -EIO;
	}
	if (enable)
		msg.buf = msg_enable;
	else
		msg.buf = msg_disable;
	if (i2c_transfer(&dev->i2c_adap, &msg, 1) != 1) {
		pr_warn("could not access the I2C gate\n");
		return -EIO;
	}
	msleep(20);
	return 0;
}