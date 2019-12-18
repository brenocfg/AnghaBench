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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int I2C_RETRY_COUNT ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_warn (struct v4l2_subdev*,char*,int) ; 

__attribute__((used)) static int tvp7002_write(struct v4l2_subdev *sd, u8 addr, u8 value)
{
	struct i2c_client *c;
	int retry;
	int error;

	c = v4l2_get_subdevdata(sd);

	for (retry = 0; retry < I2C_RETRY_COUNT; retry++) {
		error = i2c_smbus_write_byte_data(c, addr, value);

		if (error >= 0)
			return 0;

		v4l2_warn(sd, "Write: retry ... %d\n", retry);
		msleep_interruptible(10);
	}
	v4l2_err(sd, "TVP7002 write error %d\n", error);
	return error;
}