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
struct i2c_msg {unsigned short flags; int addr; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 unsigned short I2C_M_RD ; 
 int try_read_address (struct i2c_adapter*,unsigned char,int) ; 
 int try_write_address (struct i2c_adapter*,unsigned char,int) ; 

__attribute__((used)) static inline int usb_find_address(struct i2c_adapter *i2c_adap,
				   struct i2c_msg *msg, int retries,
				   unsigned char *add)
{
	unsigned short flags = msg->flags;

	unsigned char addr;
	int ret;

	addr = (msg->addr << 1);
	if (flags & I2C_M_RD)
		addr |= 1;

	add[0] = addr;
	if (flags & I2C_M_RD)
		ret = try_read_address(i2c_adap, addr, retries);
	else
		ret = try_write_address(i2c_adap, addr, retries);

	if (ret != 1)
		return -EREMOTEIO;

	return 0;
}