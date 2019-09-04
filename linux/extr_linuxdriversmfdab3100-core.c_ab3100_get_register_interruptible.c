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
struct ab3100 {int /*<<< orphan*/  access_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab3100_get_register_interruptible(struct ab3100 *ab3100,
					     u8 reg, u8 *regval)
{
	int err;

	err = mutex_lock_interruptible(&ab3100->access_mutex);
	if (err)
		return err;

	/*
	 * AB3100 require an I2C "stop" command between each message, else
	 * it will not work. The only way of achieveing this with the
	 * message transport layer is to send the read and write messages
	 * separately.
	 */
	err = i2c_master_send(ab3100->i2c_client, &reg, 1);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (send register address): %d\n",
			err);
		goto get_reg_out_unlock;
	} else if (err != 1) {
		dev_err(ab3100->dev,
			"write error (send register address)\n"
			"  %d bytes transferred (expected 1)\n",
			err);
		err = -EIO;
		goto get_reg_out_unlock;
	} else {
		/* All is well */
		err = 0;
	}

	err = i2c_master_recv(ab3100->i2c_client, regval, 1);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (read register): %d\n",
			err);
		goto get_reg_out_unlock;
	} else if (err != 1) {
		dev_err(ab3100->dev,
			"write error (read register)\n"
			"  %d bytes transferred (expected 1)\n",
			err);
		err = -EIO;
		goto get_reg_out_unlock;
	} else {
		/* All is well */
		err = 0;
	}

 get_reg_out_unlock:
	mutex_unlock(&ab3100->access_mutex);
	return err;
}