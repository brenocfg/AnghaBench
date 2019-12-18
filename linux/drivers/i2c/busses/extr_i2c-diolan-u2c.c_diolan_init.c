#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct i2c_diolan_u2c {TYPE_3__* usb_dev; TYPE_1__* interface; } ;
struct TYPE_6__ {int /*<<< orphan*/  devnum; TYPE_2__* bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  busnum; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOLAN_SYNC_TIMEOUT ; 
 int U2C_I2C_FREQ (int) ; 
 int U2C_I2C_FREQ_FAST ; 
 int U2C_I2C_FREQ_STD ; 
 int U2C_I2C_SPEED (int) ; 
 int U2C_I2C_SPEED_2KHZ ; 
 int U2C_I2C_SPEED_FAST ; 
 int U2C_I2C_SPEED_STD ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  diolan_flush_input (struct i2c_diolan_u2c*) ; 
 int /*<<< orphan*/  diolan_fw_version (struct i2c_diolan_u2c*) ; 
 int /*<<< orphan*/  diolan_get_serial (struct i2c_diolan_u2c*) ; 
 int diolan_set_clock_synch (struct i2c_diolan_u2c*,int) ; 
 int diolan_set_clock_synch_timeout (struct i2c_diolan_u2c*,int /*<<< orphan*/ ) ; 
 int diolan_set_speed (struct i2c_diolan_u2c*,int) ; 
 int frequency ; 

__attribute__((used)) static int diolan_init(struct i2c_diolan_u2c *dev)
{
	int speed, ret;

	if (frequency >= 200000) {
		speed = U2C_I2C_SPEED_FAST;
		frequency = U2C_I2C_FREQ_FAST;
	} else if (frequency >= 100000 || frequency == 0) {
		speed = U2C_I2C_SPEED_STD;
		frequency = U2C_I2C_FREQ_STD;
	} else {
		speed = U2C_I2C_SPEED(frequency);
		if (speed > U2C_I2C_SPEED_2KHZ)
			speed = U2C_I2C_SPEED_2KHZ;
		frequency = U2C_I2C_FREQ(speed);
	}

	dev_info(&dev->interface->dev,
		 "Diolan U2C at USB bus %03d address %03d speed %d Hz\n",
		 dev->usb_dev->bus->busnum, dev->usb_dev->devnum, frequency);

	diolan_flush_input(dev);
	diolan_fw_version(dev);
	diolan_get_serial(dev);

	/* Set I2C speed */
	ret = diolan_set_speed(dev, speed);
	if (ret < 0)
		return ret;

	/* Configure I2C clock synchronization */
	ret = diolan_set_clock_synch(dev, speed != U2C_I2C_SPEED_FAST);
	if (ret < 0)
		return ret;

	if (speed != U2C_I2C_SPEED_FAST)
		ret = diolan_set_clock_synch_timeout(dev, DIOLAN_SYNC_TIMEOUT);

	return ret;
}