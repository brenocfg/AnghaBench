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
typedef  int u16 ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 scalar_t__ i2c_smbus_write_byte_data (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  v4l2_err (struct v4l2_subdev*,char*,int,...) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tlv320aic23b_write(struct v4l2_subdev *sd, int reg, u16 val)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int i;

	if ((reg < 0 || reg > 9) && (reg != 15)) {
		v4l2_err(sd, "Invalid register R%d\n", reg);
		return -1;
	}

	for (i = 0; i < 3; i++)
		if (i2c_smbus_write_byte_data(client,
				(reg << 1) | (val >> 8), val & 0xff) == 0)
			return 0;
	v4l2_err(sd, "I2C: cannot write %03x to register R%d\n", val, reg);
	return -1;
}