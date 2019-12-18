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
struct i2c_msg {int flags; int len; } ;

/* Variables and functions */
 int DP_REMOTE_I2C_READ_MAX_TRANSACTIONS ; 
 int I2C_M_RD ; 

__attribute__((used)) static bool remote_i2c_read_ok(const struct i2c_msg msgs[], int num)
{
	int i;

	if (num - 1 > DP_REMOTE_I2C_READ_MAX_TRANSACTIONS)
		return false;

	for (i = 0; i < num - 1; i++) {
		if (msgs[i].flags & I2C_M_RD ||
		    msgs[i].len > 0xff)
			return false;
	}

	return msgs[num - 1].flags & I2C_M_RD &&
		msgs[num - 1].len <= 0xff;
}