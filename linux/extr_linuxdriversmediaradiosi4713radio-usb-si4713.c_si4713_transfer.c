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
struct si4713_usb_device {int dummy; } ;
struct i2c_msg {int flags; int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_M_RD ; 
 struct si4713_usb_device* i2c_get_adapdata (struct i2c_adapter*) ; 
 int si4713_i2c_read (struct si4713_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int si4713_i2c_write (struct si4713_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int si4713_transfer(struct i2c_adapter *i2c_adapter,
				struct i2c_msg *msgs, int num)
{
	struct si4713_usb_device *radio = i2c_get_adapdata(i2c_adapter);
	int retval = -EINVAL;
	int i;

	for (i = 0; i < num; i++) {
		if (msgs[i].flags & I2C_M_RD)
			retval = si4713_i2c_read(radio, msgs[i].buf, msgs[i].len);
		else
			retval = si4713_i2c_write(radio, msgs[i].buf, msgs[i].len);
		if (retval)
			break;
	}

	return retval ? retval : num;
}