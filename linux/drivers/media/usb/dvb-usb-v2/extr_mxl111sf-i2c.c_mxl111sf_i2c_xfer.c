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
struct mxl111sf_state {scalar_t__ chip_rev; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct i2c_adapter {int dummy; } ;
struct dvb_usb_device {int /*<<< orphan*/  i2c_mutex; struct mxl111sf_state* priv; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EREMOTEIO ; 
 int I2C_M_RD ; 
 scalar_t__ MXL111SF_V6 ; 
 struct dvb_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int mxl111sf_i2c_hw_xfer_msg (struct mxl111sf_state*,struct i2c_msg*) ; 
 int mxl111sf_i2c_sw_xfer_msg (struct mxl111sf_state*,struct i2c_msg*) ; 
 int /*<<< orphan*/  mxl_debug_adv (char*,int,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mxl_fail (int) ; 

int mxl111sf_i2c_xfer(struct i2c_adapter *adap,
		      struct i2c_msg msg[], int num)
{
	struct dvb_usb_device *d = i2c_get_adapdata(adap);
	struct mxl111sf_state *state = d->priv;
	int hwi2c = (state->chip_rev > MXL111SF_V6);
	int i, ret;

	if (mutex_lock_interruptible(&d->i2c_mutex) < 0)
		return -EAGAIN;

	for (i = 0; i < num; i++) {
		ret = (hwi2c) ?
			mxl111sf_i2c_hw_xfer_msg(state, &msg[i]) :
			mxl111sf_i2c_sw_xfer_msg(state, &msg[i]);
		if (mxl_fail(ret)) {
			mxl_debug_adv("failed with error %d on i2c transaction %d of %d, %sing %d bytes to/from 0x%02x",
				      ret, i+1, num,
				      (msg[i].flags & I2C_M_RD) ?
				      "read" : "writ",
				      msg[i].len, msg[i].addr);

			break;
		}
	}

	mutex_unlock(&d->i2c_mutex);

	return i == num ? num : -EREMOTEIO;
}