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
typedef  int u8 ;
struct ab3100 {int chip_id; int /*<<< orphan*/  access_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  i2c_client; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int*,int) ; 
 int i2c_master_send (int /*<<< orphan*/ ,int*,int) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ab3100_get_register_page_interruptible(struct ab3100 *ab3100,
			     u8 first_reg, u8 *regvals, u8 numregs)
{
	int err;

	if (ab3100->chip_id == 0xa0 ||
	    ab3100->chip_id == 0xa1)
		/* These don't support paged reads */
		return -EIO;

	err = mutex_lock_interruptible(&ab3100->access_mutex);
	if (err)
		return err;

	/*
	 * Paged read also require an I2C "stop" command.
	 */
	err = i2c_master_send(ab3100->i2c_client, &first_reg, 1);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (send first register address): %d\n",
			err);
		goto get_reg_page_out_unlock;
	} else if (err != 1) {
		dev_err(ab3100->dev,
			"write error (send first register address)\n"
			"  %d bytes transferred (expected 1)\n",
			err);
		err = -EIO;
		goto get_reg_page_out_unlock;
	}

	err = i2c_master_recv(ab3100->i2c_client, regvals, numregs);
	if (err < 0) {
		dev_err(ab3100->dev,
			"write error (read register page): %d\n",
			err);
		goto get_reg_page_out_unlock;
	} else if (err != numregs) {
		dev_err(ab3100->dev,
			"write error (read register page)\n"
			"  %d bytes transferred (expected %d)\n",
			err, numregs);
		err = -EIO;
		goto get_reg_page_out_unlock;
	}

	/* All is well */
	err = 0;

 get_reg_page_out_unlock:
	mutex_unlock(&ab3100->access_mutex);
	return err;
}