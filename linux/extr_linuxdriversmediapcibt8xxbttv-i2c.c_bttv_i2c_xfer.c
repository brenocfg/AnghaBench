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
struct v4l2_device {int dummy; } ;
struct i2c_msg {int flags; } ;
struct i2c_adapter {int dummy; } ;
struct bttv {int dummy; } ;

/* Variables and functions */
 int BT848_INT_I2CDONE ; 
 int BT848_INT_RACK ; 
 int /*<<< orphan*/  BT848_INT_STAT ; 
 int I2C_M_RD ; 
 int bttv_i2c_readbytes (struct bttv*,struct i2c_msg*,int) ; 
 int bttv_i2c_sendbytes (struct bttv*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 scalar_t__ i2c_debug ; 
 struct v4l2_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 struct bttv* to_bttv (struct v4l2_device*) ; 

__attribute__((used)) static int bttv_i2c_xfer(struct i2c_adapter *i2c_adap, struct i2c_msg *msgs, int num)
{
	struct v4l2_device *v4l2_dev = i2c_get_adapdata(i2c_adap);
	struct bttv *btv = to_bttv(v4l2_dev);
	int retval = 0;
	int i;

	if (i2c_debug)
		pr_debug("bt-i2c:");

	btwrite(BT848_INT_I2CDONE|BT848_INT_RACK, BT848_INT_STAT);
	for (i = 0 ; i < num; i++) {
		if (msgs[i].flags & I2C_M_RD) {
			/* read */
			retval = bttv_i2c_readbytes(btv, &msgs[i], i+1 == num);
			if (retval < 0)
				goto err;
		} else {
			/* write */
			retval = bttv_i2c_sendbytes(btv, &msgs[i], i+1 == num);
			if (retval < 0)
				goto err;
		}
	}
	return num;

 err:
	return retval;
}