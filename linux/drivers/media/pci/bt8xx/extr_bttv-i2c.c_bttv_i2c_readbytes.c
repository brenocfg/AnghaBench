#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct i2c_msg {int len; int addr; int* buf; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_I2C ; 
 int BT848_I2C_W3B ; 
 int BT878_I2C_NOSTART ; 
 int BT878_I2C_NOSTOP ; 
 int EIO ; 
 int I2C_HW ; 
 scalar_t__ btread (int /*<<< orphan*/ ) ; 
 int bttv_i2c_wait_done (struct bttv*) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_debug ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static int
bttv_i2c_readbytes(struct bttv *btv, const struct i2c_msg *msg, int last)
{
	u32 xmit;
	u32 cnt;
	int retval;

	for (cnt = 0; cnt < msg->len; cnt++) {
		xmit = (msg->addr << 25) | (1 << 24) | I2C_HW;
		if (cnt < msg->len-1)
			xmit |= BT848_I2C_W3B;
		if (cnt < msg->len-1 || !last)
			xmit |= BT878_I2C_NOSTOP;
		if (cnt)
			xmit |= BT878_I2C_NOSTART;

		if (i2c_debug) {
			if (!(xmit & BT878_I2C_NOSTART))
				pr_cont(" <R %02x", (msg->addr << 1) +1);
		}

		btwrite(xmit, BT848_I2C);
		retval = bttv_i2c_wait_done(btv);
		if (retval < 0)
			goto err;
		if (retval == 0)
			goto eio;
		msg->buf[cnt] = ((u32)btread(BT848_I2C) >> 8) & 0xff;
		if (i2c_debug) {
			pr_cont(" =%02x", msg->buf[cnt]);
		}
		if (i2c_debug && !(xmit & BT878_I2C_NOSTOP))
			pr_cont(" >\n");
	}


	return msg->len;

 eio:
	retval = -EIO;
 err:
	if (i2c_debug)
		pr_cont(" ERR: %d\n",retval);
	return retval;
}