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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sis630_transaction_end (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int sis630_transaction_start (struct i2c_adapter*,int,int /*<<< orphan*/ *) ; 
 int sis630_transaction_wait (struct i2c_adapter*,int) ; 

__attribute__((used)) static int sis630_transaction(struct i2c_adapter *adap, int size)
{
	int result = 0;
	u8 oldclock = 0;

	result = sis630_transaction_start(adap, size, &oldclock);
	if (!result) {
		result = sis630_transaction_wait(adap, size);
		sis630_transaction_end(adap, oldclock);
	}

	return result;
}