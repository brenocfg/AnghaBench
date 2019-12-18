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
struct i2c_msg {int addr; int len; int* buf; int /*<<< orphan*/  flags; } ;
struct i2c_device {int addr; int* i2c_write_buffer; int* i2c_read_buffer; int /*<<< orphan*/  i2c_buffer_lock; int /*<<< orphan*/  adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_M_RD ; 
 int /*<<< orphan*/  dprintk (char*,...) ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 dib8000_i2c_read16(struct i2c_device *i2c, u16 reg)
{
	u16 ret;
	struct i2c_msg msg[2] = {
		{.addr = i2c->addr >> 1, .flags = 0, .len = 2},
		{.addr = i2c->addr >> 1, .flags = I2C_M_RD, .len = 2},
	};

	if (mutex_lock_interruptible(i2c->i2c_buffer_lock) < 0) {
		dprintk("could not acquire lock\n");
		return 0;
	}

	msg[0].buf    = i2c->i2c_write_buffer;
	msg[0].buf[0] = reg >> 8;
	msg[0].buf[1] = reg & 0xff;
	msg[1].buf    = i2c->i2c_read_buffer;

	if (i2c_transfer(i2c->adap, msg, 2) != 2)
		dprintk("i2c read error on %d\n", reg);

	ret = (msg[1].buf[0] << 8) | msg[1].buf[1];
	mutex_unlock(i2c->i2c_buffer_lock);
	return ret;
}