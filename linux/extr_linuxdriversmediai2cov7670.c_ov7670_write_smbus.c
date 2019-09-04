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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 unsigned char COM7_RESET ; 
 unsigned char REG_COM7 ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov7670_write_smbus(struct v4l2_subdev *sd, unsigned char reg,
		unsigned char value)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret = i2c_smbus_write_byte_data(client, reg, value);

	if (reg == REG_COM7 && (value & COM7_RESET))
		msleep(5);  /* Wait for reset to run */
	return ret;
}