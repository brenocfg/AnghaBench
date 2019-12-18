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
struct synquacer_i2c {int timeout_ms; int /*<<< orphan*/  dev; } ;
struct i2c_msg {int dummy; } ;
struct i2c_adapter {int retries; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EIO ; 
 int calc_timeout_ms (struct synquacer_i2c*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 struct synquacer_i2c* i2c_get_adapdata (struct i2c_adapter*) ; 
 int synquacer_i2c_doxfer (struct synquacer_i2c*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  synquacer_i2c_hw_reset (struct synquacer_i2c*) ; 

__attribute__((used)) static int synquacer_i2c_xfer(struct i2c_adapter *adap, struct i2c_msg *msgs,
			      int num)
{
	struct synquacer_i2c *i2c;
	int retry;
	int ret;

	i2c = i2c_get_adapdata(adap);
	i2c->timeout_ms = calc_timeout_ms(i2c, msgs, num);

	dev_dbg(i2c->dev, "calculated timeout %d ms\n", i2c->timeout_ms);

	for (retry = 0; retry <= adap->retries; retry++) {
		ret = synquacer_i2c_doxfer(i2c, msgs, num);
		if (ret != -EAGAIN)
			return ret;

		dev_dbg(i2c->dev, "Retrying transmission (%d)\n", retry);

		synquacer_i2c_hw_reset(i2c);
	}
	return -EIO;
}