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
struct i2c_msg {int flags; } ;
struct i2c_algo_pcf_data {int dummy; } ;

/* Variables and functions */
 int I2C_M_REV_DIR_ADDR ; 
 unsigned char i2c_8bit_addr_from_msg (struct i2c_msg*) ; 
 int /*<<< orphan*/  i2c_outb (struct i2c_algo_pcf_data*,unsigned char) ; 

__attribute__((used)) static int pcf_doAddress(struct i2c_algo_pcf_data *adap,
			 struct i2c_msg *msg)
{
	unsigned char addr = i2c_8bit_addr_from_msg(msg);

	if (msg->flags & I2C_M_REV_DIR_ADDR)
		addr ^= 1;
	i2c_outb(adap, addr);

	return 0;
}