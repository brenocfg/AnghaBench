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
typedef  scalar_t__ u16 ;
struct i2c_device_addr {int /*<<< orphan*/  user_data; int /*<<< orphan*/  i2c_dev_id; int /*<<< orphan*/  i2c_addr; } ;
struct drx_demod_instance {struct i2c_device_addr* my_i2c_dev_addr; } ;

/* Variables and functions */
 scalar_t__ DRXJ_MAX_RETRIES_POWERUP ; 
 int /*<<< orphan*/  DRXJ_WAKE_UP_KEY ; 
 int EIO ; 
 scalar_t__ drxbsp_i2c_write_read (struct i2c_device_addr*,int,scalar_t__*,struct i2c_device_addr*,int,scalar_t__*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int power_up_device(struct drx_demod_instance *demod)
{
	struct i2c_device_addr *dev_addr = (struct i2c_device_addr *)(NULL);
	u8 data = 0;
	u16 retry_count = 0;
	struct i2c_device_addr wake_up_addr;

	dev_addr = demod->my_i2c_dev_addr;
	wake_up_addr.i2c_addr = DRXJ_WAKE_UP_KEY;
	wake_up_addr.i2c_dev_id = dev_addr->i2c_dev_id;
	wake_up_addr.user_data = dev_addr->user_data;
	/*
	 * I2C access may fail in this case: no ack
	 * dummy write must be used to wake uop device, dummy read must be used to
	 * reset HI state machine (avoiding actual writes)
	 */
	do {
		data = 0;
		drxbsp_i2c_write_read(&wake_up_addr, 1, &data,
				      (struct i2c_device_addr *)(NULL), 0,
				     (u8 *)(NULL));
		msleep(10);
		retry_count++;
	} while ((drxbsp_i2c_write_read
		  ((struct i2c_device_addr *) (NULL), 0, (u8 *)(NULL), dev_addr, 1,
		   &data)
		  != 0) && (retry_count < DRXJ_MAX_RETRIES_POWERUP));

	/* Need some recovery time .... */
	msleep(10);

	if (retry_count == DRXJ_MAX_RETRIES_POWERUP)
		return -EIO;

	return 0;
}