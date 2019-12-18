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
struct i2c_algo_pcf_data {int dummy; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; struct i2c_algo_pcf_data* algo_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEB2 (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int EREMOTEIO ; 
 int I2C_PCF_LRB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,char const) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_outb (struct i2c_algo_pcf_data*,char const) ; 
 int /*<<< orphan*/  i2c_repstart (struct i2c_algo_pcf_data*) ; 
 int /*<<< orphan*/  i2c_stop (struct i2c_algo_pcf_data*) ; 
 int wait_for_pin (struct i2c_algo_pcf_data*,int*) ; 

__attribute__((used)) static int pcf_sendbytes(struct i2c_adapter *i2c_adap, const char *buf,
			 int count, int last)
{
	struct i2c_algo_pcf_data *adap = i2c_adap->algo_data;
	int wrcount, status, timeout;

	for (wrcount=0; wrcount<count; ++wrcount) {
		DEB2(dev_dbg(&i2c_adap->dev, "i2c_write: writing %2.2X\n",
				buf[wrcount] & 0xff));
		i2c_outb(adap, buf[wrcount]);
		timeout = wait_for_pin(adap, &status);
		if (timeout) {
			if (timeout == -EINTR)
				return -EINTR; /* arbitration lost */

			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "i2c_write: error - timeout.\n");
			return -EREMOTEIO; /* got a better one ?? */
		}
		if (status & I2C_PCF_LRB) {
			i2c_stop(adap);
			dev_err(&i2c_adap->dev, "i2c_write: error - no ack.\n");
			return -EREMOTEIO; /* got a better one ?? */
		}
	}
	if (last)
		i2c_stop(adap);
	else
		i2c_repstart(adap);

	return wrcount;
}