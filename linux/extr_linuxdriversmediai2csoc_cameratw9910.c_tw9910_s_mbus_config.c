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
struct v4l2_mbus_config {int dummy; } ;
struct soc_camera_subdev_desc {int dummy; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int HSP_HI ; 
 int HSSL_DVALID ; 
 int /*<<< orphan*/  OUTCTR1 ; 
 unsigned long V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 unsigned long V4L2_MBUS_VSYNC_ACTIVE_LOW ; 
 int VSP_HI ; 
 int VSSL_VVALID ; 
 int i2c_smbus_write_byte_data (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 unsigned long soc_camera_apply_board_flags (struct soc_camera_subdev_desc*,struct v4l2_mbus_config const*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int tw9910_s_mbus_config(struct v4l2_subdev *sd,
				const struct v4l2_mbus_config *cfg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	u8 val = VSSL_VVALID | HSSL_DVALID;
	unsigned long flags = soc_camera_apply_board_flags(ssdd, cfg);

	/*
	 * set OUTCTR1
	 *
	 * We use VVALID and DVALID signals to control VSYNC and HSYNC
	 * outputs, in this mode their polarity is inverted.
	 */
	if (flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		val |= HSP_HI;

	if (flags & V4L2_MBUS_VSYNC_ACTIVE_LOW)
		val |= VSP_HI;

	return i2c_smbus_write_byte_data(client, OUTCTR1, val);
}