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
struct i2c_msg {int flags; } ;
struct i2c_adapter {int retries; scalar_t__ timeout; TYPE_1__* algo; scalar_t__ quirks; } ;
struct TYPE_2__ {int (* master_xfer ) (struct i2c_adapter*,struct i2c_msg*,int) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int I2C_M_RD ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ i2c_check_for_quirks (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  i2c_trace_msg_key ; 
 unsigned long jiffies ; 
 scalar_t__ static_branch_unlikely (int /*<<< orphan*/ *) ; 
 int stub1 (struct i2c_adapter*,struct i2c_msg*,int) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  trace_i2c_read (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  trace_i2c_reply (struct i2c_adapter*,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  trace_i2c_result (struct i2c_adapter*,int,int) ; 
 int /*<<< orphan*/  trace_i2c_write (struct i2c_adapter*,struct i2c_msg*,int) ; 

int __i2c_transfer(struct i2c_adapter *adap, struct i2c_msg *msgs, int num)
{
	unsigned long orig_jiffies;
	int ret, try;

	if (WARN_ON(!msgs || num < 1))
		return -EINVAL;

	if (adap->quirks && i2c_check_for_quirks(adap, msgs, num))
		return -EOPNOTSUPP;

	/*
	 * i2c_trace_msg_key gets enabled when tracepoint i2c_transfer gets
	 * enabled.  This is an efficient way of keeping the for-loop from
	 * being executed when not needed.
	 */
	if (static_branch_unlikely(&i2c_trace_msg_key)) {
		int i;
		for (i = 0; i < num; i++)
			if (msgs[i].flags & I2C_M_RD)
				trace_i2c_read(adap, &msgs[i], i);
			else
				trace_i2c_write(adap, &msgs[i], i);
	}

	/* Retry automatically on arbitration loss */
	orig_jiffies = jiffies;
	for (ret = 0, try = 0; try <= adap->retries; try++) {
		ret = adap->algo->master_xfer(adap, msgs, num);
		if (ret != -EAGAIN)
			break;
		if (time_after(jiffies, orig_jiffies + adap->timeout))
			break;
	}

	if (static_branch_unlikely(&i2c_trace_msg_key)) {
		int i;
		for (i = 0; i < ret; i++)
			if (msgs[i].flags & I2C_M_RD)
				trace_i2c_reply(adap, &msgs[i], i);
		trace_i2c_result(adap, num, ret);
	}

	return ret;
}