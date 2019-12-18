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
typedef  int u16 ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct i2c_device {int i2c_addr; int* i2c_write_buffer; int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int EREMOTEIO ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int dib9000_i2c_write16(struct i2c_device *i2c, u16 reg, u16 val)
{
	struct i2c_msg msg = {
		.addr = i2c->i2c_addr >> 1, .flags = 0,
		.buf = i2c->i2c_write_buffer, .len = 4
	};

	i2c->i2c_write_buffer[0] = (reg >> 8) & 0xff;
	i2c->i2c_write_buffer[1] = reg & 0xff;
	i2c->i2c_write_buffer[2] = (val >> 8) & 0xff;
	i2c->i2c_write_buffer[3] = val & 0xff;

	return i2c_transfer(i2c->i2c_adap, &msg, 1) != 1 ? -EREMOTEIO : 0;
}