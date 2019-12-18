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
struct i2c_msg {int flags; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  timeout; } ;
struct hix5hd2_i2c_priv {int stop; int err; int state; TYPE_1__ adap; int /*<<< orphan*/  dev; int /*<<< orphan*/  msg_complete; struct i2c_msg* msg; int /*<<< orphan*/  msg_len; scalar_t__ msg_idx; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int HIX5I2C_STAT_INIT ; 
 int HIX5I2C_STAT_RW_ERR ; 
 int HIX5I2C_STAT_RW_SUCCESS ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hix5hd2_i2c_message_start (struct hix5hd2_i2c_priv*,int) ; 
 int /*<<< orphan*/  hix5hd2_i2c_reset (struct hix5hd2_i2c_priv*) ; 
 int hix5hd2_i2c_wait_bus_idle (struct hix5hd2_i2c_priv*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 unsigned long wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hix5hd2_i2c_xfer_msg(struct hix5hd2_i2c_priv *priv,
				struct i2c_msg *msgs, int stop)
{
	unsigned long timeout;
	int ret;

	priv->msg = msgs;
	priv->msg_idx = 0;
	priv->msg_len = priv->msg->len;
	priv->stop = stop;
	priv->err = 0;
	priv->state = HIX5I2C_STAT_INIT;

	reinit_completion(&priv->msg_complete);
	hix5hd2_i2c_message_start(priv, stop);

	timeout = wait_for_completion_timeout(&priv->msg_complete,
					      priv->adap.timeout);
	if (timeout == 0) {
		priv->state = HIX5I2C_STAT_RW_ERR;
		priv->err = -ETIMEDOUT;
		dev_warn(priv->dev, "%s timeout=%d\n",
			 msgs->flags & I2C_M_RD ? "rx" : "tx",
			 priv->adap.timeout);
	}
	ret = priv->state;

	/*
	 * If this is the last message to be transfered (stop == 1)
	 * Then check if the bus can be brought back to idle.
	 */
	if (priv->state == HIX5I2C_STAT_RW_SUCCESS && stop)
		ret = hix5hd2_i2c_wait_bus_idle(priv);

	if (ret < 0)
		hix5hd2_i2c_reset(priv);

	return priv->err;
}