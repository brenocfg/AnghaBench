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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int I2C_RETRY_COUNT ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,scalar_t__) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvp7002_read(struct v4l2_subdev *sd, u8 addr, u8 *dst)
{
	struct i2c_client *c = v4l2_get_subdevdata(sd);
	int retry;
	int error;

	for (retry = 0; retry < I2C_RETRY_COUNT; retry++) {
		error = i2c_smbus_read_byte_data(c, addr);

		if (error >= 0) {
			*dst = (u8)error;
			return 0;
		}

		msleep_interruptible(10);
	}
	v4l2_err(sd, "TVP7002 read error %d\n", error);
	return error;
}