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
struct i2c_msg {int flags; int /*<<< orphan*/  buf; int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ETIMEDOUT ; 
 int I2C_M_RD ; 
 int /*<<< orphan*/  i2c_recover_bus (struct i2c_adapter*) ; 
 int uniphier_i2c_rx (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int uniphier_i2c_stop (struct i2c_adapter*) ; 
 int uniphier_i2c_tx (struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int uniphier_i2c_master_xfer_one(struct i2c_adapter *adap,
					struct i2c_msg *msg, bool stop)
{
	bool is_read = msg->flags & I2C_M_RD;
	bool recovery = false;
	int ret;

	if (is_read)
		ret = uniphier_i2c_rx(adap, msg->addr, msg->len, msg->buf);
	else
		ret = uniphier_i2c_tx(adap, msg->addr, msg->len, msg->buf);

	if (ret == -EAGAIN) /* could not acquire bus. bail out without STOP */
		return ret;

	if (ret == -ETIMEDOUT) {
		/* This error is fatal.  Needs recovery. */
		stop = false;
		recovery = true;
	}

	if (stop) {
		int ret2 = uniphier_i2c_stop(adap);

		if (ret2) {
			/* Failed to issue STOP.  The bus needs recovery. */
			recovery = true;
			ret = ret ?: ret2;
		}
	}

	if (recovery)
		i2c_recover_bus(adap);

	return ret;
}