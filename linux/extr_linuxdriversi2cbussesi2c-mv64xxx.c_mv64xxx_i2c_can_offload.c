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
struct mv64xxx_i2c_data {int num_msgs; int /*<<< orphan*/  offload_enabled; struct i2c_msg* msgs; } ;
struct i2c_msg {int flags; } ;

/* Variables and functions */
 int I2C_M_RD ; 
 scalar_t__ mv64xxx_i2c_valid_offload_sz (struct i2c_msg*) ; 

__attribute__((used)) static bool
mv64xxx_i2c_can_offload(struct mv64xxx_i2c_data *drv_data)
{
	struct i2c_msg *msgs = drv_data->msgs;
	int num = drv_data->num_msgs;

	if (!drv_data->offload_enabled)
		return false;

	/*
	 * We can offload a transaction consisting of a single
	 * message, as long as the message has a length between 1 and
	 * 8 bytes.
	 */
	if (num == 1 && mv64xxx_i2c_valid_offload_sz(msgs))
		return true;

	/*
	 * We can offload a transaction consisting of two messages, if
	 * the first is a write and a second is a read, and both have
	 * a length between 1 and 8 bytes.
	 */
	if (num == 2 &&
	    mv64xxx_i2c_valid_offload_sz(msgs) &&
	    mv64xxx_i2c_valid_offload_sz(msgs + 1) &&
	    !(msgs[0].flags & I2C_M_RD) &&
	    msgs[1].flags & I2C_M_RD)
		return true;

	return false;
}