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
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; TYPE_1__* algo; } ;
struct TYPE_2__ {scalar_t__ master_xfer; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 int __i2c_transfer (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_lock_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int i2c_trylock_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unlock_bus (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ in_atomic () ; 
 scalar_t__ irqs_disabled () ; 

int i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
	int ret;

	/* REVISIT the fault reporting model here is weak:
	 *
	 *  - When we get an error after receiving N bytes from a slave,
	 *    there is no way to report "N".
	 *
	 *  - When we get a NAK after transmitting N bytes to a slave,
	 *    there is no way to report "N" ... or to let the master
	 *    continue executing the rest of this combined message, if
	 *    that's the appropriate response.
	 *
	 *  - When for example "num" is two and we successfully complete
	 *    the first message but get an error part way through the
	 *    second, it's unclear whether that should be reported as
	 *    one (discarding status on the second message) or errno
	 *    (discarding status on the first one).
	 */

	if (adap->algo->master_xfer) {
#ifdef DEBUG
		for (ret = 0; ret < num; ret++) {
			dev_dbg(&adap->dev,
				"master_xfer[%d] %c, addr=0x%02x, len=%d%s\n",
				ret, (msgs[ret].flags & I2C_M_RD) ? 'R' : 'W',
				msgs[ret].addr, msgs[ret].len,
				(msgs[ret].flags & I2C_M_RECV_LEN) ? "+" : "");
		}
#endif

		if (in_atomic() || irqs_disabled()) {
			ret = i2c_trylock_bus(adap, I2C_LOCK_SEGMENT);
			if (!ret)
				/* I2C activity is ongoing. */
				return -EAGAIN;
		} else {
			i2c_lock_bus(adap, I2C_LOCK_SEGMENT);
		}

		ret = __i2c_transfer(adap, msgs, num);
		i2c_unlock_bus(adap, I2C_LOCK_SEGMENT);

		return ret;
	} else {
		dev_dbg(&adap->dev, "I2C level transfers not supported\n");
		return -EOPNOTSUPP;
	}
}