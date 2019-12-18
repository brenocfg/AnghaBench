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
typedef  scalar_t__ u8 ;
struct radeon_i2c_chan {int /*<<< orphan*/  adapter; } ;
struct i2c_msg {int len; scalar_t__* buf; int /*<<< orphan*/  flags; scalar_t__ addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  I2C_M_RD ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

void radeon_i2c_get_byte(struct radeon_i2c_chan *i2c_bus,
			 u8 slave_addr,
			 u8 addr,
			 u8 *val)
{
	u8 out_buf[2];
	u8 in_buf[2];
	struct i2c_msg msgs[] = {
		{
			.addr = slave_addr,
			.flags = 0,
			.len = 1,
			.buf = out_buf,
		},
		{
			.addr = slave_addr,
			.flags = I2C_M_RD,
			.len = 1,
			.buf = in_buf,
		}
	};

	out_buf[0] = addr;
	out_buf[1] = 0;

	if (i2c_transfer(&i2c_bus->adapter, msgs, 2) == 2) {
		*val = in_buf[0];
		DRM_DEBUG("val = 0x%02x\n", *val);
	} else {
		DRM_DEBUG("i2c 0x%02x 0x%02x read failed\n",
			  addr, *val);
	}
}