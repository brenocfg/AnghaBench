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
union i2c_smbus_data {int /*<<< orphan*/  byte; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct i2c_adapter {int dummy; } ;
struct cafe_camera {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int I2C_SMBUS_BYTE_DATA ; 
 char I2C_SMBUS_READ ; 
 char I2C_SMBUS_WRITE ; 
 int cafe_smbus_read_data (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int cafe_smbus_write_data (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_err (struct cafe_camera*,char*,int) ; 
 struct cafe_camera* i2c_get_adapdata (struct i2c_adapter*) ; 

__attribute__((used)) static int cafe_smbus_xfer(struct i2c_adapter *adapter, u16 addr,
		unsigned short flags, char rw, u8 command,
		int size, union i2c_smbus_data *data)
{
	struct cafe_camera *cam = i2c_get_adapdata(adapter);
	int ret = -EINVAL;

	/*
	 * This interface would appear to only do byte data ops.  OK
	 * it can do word too, but the cam chip has no use for that.
	 */
	if (size != I2C_SMBUS_BYTE_DATA) {
		cam_err(cam, "funky xfer size %d\n", size);
		return -EINVAL;
	}

	if (rw == I2C_SMBUS_WRITE)
		ret = cafe_smbus_write_data(cam, addr, command, data->byte);
	else if (rw == I2C_SMBUS_READ)
		ret = cafe_smbus_read_data(cam, addr, command, &data->byte);
	return ret;
}