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
struct i2c_client {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_LOCK_SEGMENT ; 
 int /*<<< orphan*/  i2c_lock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_unlock_bus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_device (struct i2c_client*,int,int,unsigned char*) ; 

int pm860x_page_bulk_read(struct i2c_client *i2c, int reg,
			  int count, unsigned char *buf)
{
	unsigned char zero = 0;
	int ret;

	i2c_lock_bus(i2c->adapter, I2C_LOCK_SEGMENT);
	read_device(i2c, 0xfa, 0, &zero);
	read_device(i2c, 0xfb, 0, &zero);
	read_device(i2c, 0xff, 0, &zero);
	ret = read_device(i2c, reg, count, buf);
	read_device(i2c, 0xFE, 0, &zero);
	read_device(i2c, 0xFC, 0, &zero);
	i2c_unlock_bus(i2c->adapter, I2C_LOCK_SEGMENT);
	return ret;
}