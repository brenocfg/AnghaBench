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
struct i2c_msg {int flags; } ;
struct i2c_adapter {int /*<<< orphan*/  timeout; } ;
struct bcm2835_i2c_dev {int num_msgs; int msg_err; int /*<<< orphan*/  dev; int /*<<< orphan*/  completion; struct i2c_msg* curr_msg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM2835_I2C_C ; 
 int /*<<< orphan*/  BCM2835_I2C_C_CLEAR ; 
 int BCM2835_I2C_S_ERR ; 
 int EIO ; 
 int EOPNOTSUPP ; 
 int EREMOTEIO ; 
 int ETIMEDOUT ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  bcm2835_i2c_finish_transfer (struct bcm2835_i2c_dev*) ; 
 int /*<<< orphan*/  bcm2835_i2c_start_transfer (struct bcm2835_i2c_dev*) ; 
 int /*<<< orphan*/  bcm2835_i2c_writel (struct bcm2835_i2c_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn_once (int /*<<< orphan*/ ,char*) ; 
 struct bcm2835_i2c_dev* i2c_get_adapdata (struct i2c_adapter*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bcm2835_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg msgs[],
			    int num)
{
	struct bcm2835_i2c_dev *i2c_dev = i2c_get_adapdata(adap);
	unsigned long time_left;
	int i;

	for (i = 0; i < (num - 1); i++)
		if (msgs[i].flags & I2C_M_RD) {
			dev_warn_once(i2c_dev->dev,
				      "only one read message supported, has to be last\n");
			return -EOPNOTSUPP;
		}

	i2c_dev->curr_msg = msgs;
	i2c_dev->num_msgs = num;
	reinit_completion(&i2c_dev->completion);

	bcm2835_i2c_start_transfer(i2c_dev);

	time_left = wait_for_completion_timeout(&i2c_dev->completion,
						adap->timeout);

	bcm2835_i2c_finish_transfer(i2c_dev);

	if (!time_left) {
		bcm2835_i2c_writel(i2c_dev, BCM2835_I2C_C,
				   BCM2835_I2C_C_CLEAR);
		dev_err(i2c_dev->dev, "i2c transfer timed out\n");
		return -ETIMEDOUT;
	}

	if (!i2c_dev->msg_err)
		return num;

	dev_dbg(i2c_dev->dev, "i2c transfer failed: %x\n", i2c_dev->msg_err);

	if (i2c_dev->msg_err & BCM2835_I2C_S_ERR)
		return -EREMOTEIO;

	return -EIO;
}