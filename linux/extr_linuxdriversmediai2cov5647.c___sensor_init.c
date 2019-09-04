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
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OV5647_SW_STANDBY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ov5647_640x480 ; 
 int ov5647_read (struct v4l2_subdev*,int /*<<< orphan*/ ,int*) ; 
 int ov5647_set_virtual_channel (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int ov5647_stream_off (struct v4l2_subdev*) ; 
 int ov5647_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int) ; 
 int ov5647_write_array (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int __sensor_init(struct v4l2_subdev *sd)
{
	int ret;
	u8 resetval, rdval;
	struct i2c_client *client = v4l2_get_subdevdata(sd);

	ret = ov5647_read(sd, OV5647_SW_STANDBY, &rdval);
	if (ret < 0)
		return ret;

	ret = ov5647_write_array(sd, ov5647_640x480,
					ARRAY_SIZE(ov5647_640x480));
	if (ret < 0) {
		dev_err(&client->dev, "write sensor default regs error\n");
		return ret;
	}

	ret = ov5647_set_virtual_channel(sd, 0);
	if (ret < 0)
		return ret;

	ret = ov5647_read(sd, OV5647_SW_STANDBY, &resetval);
	if (ret < 0)
		return ret;

	if (!(resetval & 0x01)) {
		dev_err(&client->dev, "Device was in SW standby");
		ret = ov5647_write(sd, OV5647_SW_STANDBY, 0x01);
		if (ret < 0)
			return ret;
	}

	/*
	 * stream off to make the clock lane into LP-11 state.
	 */
	return ov5647_stream_off(sd);
}