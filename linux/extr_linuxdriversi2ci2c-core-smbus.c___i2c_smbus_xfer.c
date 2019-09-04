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
typedef  union i2c_smbus_data {int dummy; } i2c_smbus_data ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int retries; TYPE_1__* algo; scalar_t__ timeout; } ;
typedef  int /*<<< orphan*/  s32 ;
struct TYPE_2__ {int /*<<< orphan*/  master_xfer; int /*<<< orphan*/  (* smbus_xfer ) (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  EOPNOTSUPP ; 
 unsigned short I2C_CLIENT_PEC ; 
 unsigned short I2C_CLIENT_SCCB ; 
 unsigned short I2C_M_TEN ; 
 int /*<<< orphan*/  i2c_smbus_xfer_emulated (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  stub1 (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  trace_smbus_read (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  trace_smbus_reply (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 
 int /*<<< orphan*/  trace_smbus_result (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_smbus_write (struct i2c_adapter*,int /*<<< orphan*/ ,unsigned short,char,int /*<<< orphan*/ ,int,union i2c_smbus_data*) ; 

s32 __i2c_smbus_xfer(struct i2c_adapter *adapter, u16 addr,
		     unsigned short flags, char read_write,
		     u8 command, int protocol, union i2c_smbus_data *data)
{
	unsigned long orig_jiffies;
	int try;
	s32 res;

	/* If enabled, the following two tracepoints are conditional on
	 * read_write and protocol.
	 */
	trace_smbus_write(adapter, addr, flags, read_write,
			  command, protocol, data);
	trace_smbus_read(adapter, addr, flags, read_write,
			 command, protocol);

	flags &= I2C_M_TEN | I2C_CLIENT_PEC | I2C_CLIENT_SCCB;

	if (adapter->algo->smbus_xfer) {
		/* Retry automatically on arbitration loss */
		orig_jiffies = jiffies;
		for (res = 0, try = 0; try <= adapter->retries; try++) {
			res = adapter->algo->smbus_xfer(adapter, addr, flags,
							read_write, command,
							protocol, data);
			if (res != -EAGAIN)
				break;
			if (time_after(jiffies,
				       orig_jiffies + adapter->timeout))
				break;
		}

		if (res != -EOPNOTSUPP || !adapter->algo->master_xfer)
			goto trace;
		/*
		 * Fall back to i2c_smbus_xfer_emulated if the adapter doesn't
		 * implement native support for the SMBus operation.
		 */
	}

	res = i2c_smbus_xfer_emulated(adapter, addr, flags, read_write,
				      command, protocol, data);

trace:
	/* If enabled, the reply tracepoint is conditional on read_write. */
	trace_smbus_reply(adapter, addr, flags, read_write,
			  command, protocol, data);
	trace_smbus_result(adapter, addr, flags, read_write,
			   command, protocol, res);

	return res;
}