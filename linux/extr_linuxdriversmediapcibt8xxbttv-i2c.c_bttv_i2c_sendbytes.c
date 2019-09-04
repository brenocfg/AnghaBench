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
 int BT878_I2C_NOSTART ; 
 int BT878_I2C_NOSTOP ; 
 int EINVAL ; 
 int EIO ; 
 int I2C_HW ; 
 int bttv_i2c_wait_done (struct bttv*) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_debug ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 

__attribute__((used)) static int
bttv_i2c_sendbytes(struct bttv *btv, const struct i2c_msg *msg, int last)
{
	u32 xmit;
	int retval,cnt;

	/* sanity checks */
	if (0 == msg->len)
		return -EINVAL;

	/* start, address + first byte */
	xmit = (msg->addr << 25) | (msg->buf[0] << 16) | I2C_HW;
	if (msg->len > 1 || !last)
		xmit |= BT878_I2C_NOSTOP;
	btwrite(xmit, BT848_I2C);
	retval = bttv_i2c_wait_done(btv);
	if (retval < 0)
		goto err;
	if (retval == 0)
		goto eio;
	if (i2c_debug) {
		pr_cont(" <W %02x %02x", msg->addr << 1, msg->buf[0]);
	}

	for (cnt = 1; cnt < msg->len; cnt++ ) {
		/* following bytes */
		xmit = (msg->buf[cnt] << 24) | I2C_HW | BT878_I2C_NOSTART;
		if (cnt < msg->len-1 || !last)
			xmit |= BT878_I2C_NOSTOP;
		btwrite(xmit, BT848_I2C);
		retval = bttv_i2c_wait_done(btv);
		if (retval < 0)
			goto err;
		if (retval == 0)
			goto eio;
		if (i2c_debug)
			pr_cont(" %02x", msg->buf[cnt]);
	}
	if (i2c_debug && !(xmit & BT878_I2C_NOSTOP))
		pr_cont(">\n");
	return msg->len;

 eio:
	retval = -EIO;
 err:
	if (i2c_debug)
		pr_cont(" ERR: %d\n",retval);
	return retval;
}