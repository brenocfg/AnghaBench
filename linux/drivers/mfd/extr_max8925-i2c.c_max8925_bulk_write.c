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
struct max8925_chip {int /*<<< orphan*/  io_lock; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct max8925_chip* i2c_get_clientdata (struct i2c_client*) ; 
 int max8925_write_device (struct i2c_client*,int,int,unsigned char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int max8925_bulk_write(struct i2c_client *i2c, int reg,
		int count, unsigned char *buf)
{
	struct max8925_chip *chip = i2c_get_clientdata(i2c);
	int ret;

	mutex_lock(&chip->io_lock);
	ret = max8925_write_device(i2c, reg, count, buf);
	mutex_unlock(&chip->io_lock);

	return ret;
}