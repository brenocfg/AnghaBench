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
struct v4l2_mbus_config {int dummy; } ;
struct soc_camera_subdev_desc {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT9T031_PIXEL_CLOCK_CONTROL ; 
 int V4L2_MBUS_PCLK_SAMPLE_FALLING ; 
 int reg_clear (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int reg_set (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int soc_camera_apply_board_flags (struct soc_camera_subdev_desc*,struct v4l2_mbus_config const*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int mt9t031_s_mbus_config(struct v4l2_subdev *sd,
				const struct v4l2_mbus_config *cfg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);

	if (soc_camera_apply_board_flags(ssdd, cfg) &
	    V4L2_MBUS_PCLK_SAMPLE_FALLING)
		return reg_clear(client, MT9T031_PIXEL_CLOCK_CONTROL, 0x8000);
	else
		return reg_set(client, MT9T031_PIXEL_CLOCK_CONTROL, 0x8000);
}