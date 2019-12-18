#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int width; int height; int left; int top; } ;
struct ov5642 {int total_width; int total_height; TYPE_1__ crop_rect; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int OV5642_SENSOR_SIZE_X ; 
 int OV5642_SENSOR_SIZE_Y ; 
 int /*<<< orphan*/  REG_AVG_WINDOW_END_X_HIGH ; 
 int /*<<< orphan*/  REG_AVG_WINDOW_END_Y_HIGH ; 
 int /*<<< orphan*/  REG_OUT_HEIGHT_HIGH ; 
 int /*<<< orphan*/  REG_OUT_TOTAL_HEIGHT_HIGH ; 
 int /*<<< orphan*/  REG_OUT_TOTAL_WIDTH_HIGH ; 
 int /*<<< orphan*/  REG_OUT_WIDTH_HIGH ; 
 int /*<<< orphan*/  REG_WINDOW_HEIGHT_HIGH ; 
 int /*<<< orphan*/  REG_WINDOW_START_X_HIGH ; 
 int /*<<< orphan*/  REG_WINDOW_START_Y_HIGH ; 
 int /*<<< orphan*/  REG_WINDOW_WIDTH_HIGH ; 
 int reg_write16 (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 struct ov5642* to_ov5642 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5642_set_resolution(struct v4l2_subdev *sd)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct ov5642 *priv = to_ov5642(client);
	int width = priv->crop_rect.width;
	int height = priv->crop_rect.height;
	int total_width = priv->total_width;
	int total_height = priv->total_height;
	int start_x = (OV5642_SENSOR_SIZE_X - width) / 2;
	int start_y = (OV5642_SENSOR_SIZE_Y - height) / 2;
	int ret;

	/*
	 * This should set the starting point for cropping.
	 * Doesn't work so far.
	 */
	ret = reg_write16(client, REG_WINDOW_START_X_HIGH, start_x);
	if (!ret)
		ret = reg_write16(client, REG_WINDOW_START_Y_HIGH, start_y);
	if (!ret) {
		priv->crop_rect.left = start_x;
		priv->crop_rect.top = start_y;
	}

	if (!ret)
		ret = reg_write16(client, REG_WINDOW_WIDTH_HIGH, width);
	if (!ret)
		ret = reg_write16(client, REG_WINDOW_HEIGHT_HIGH, height);
	if (ret)
		return ret;
	priv->crop_rect.width = width;
	priv->crop_rect.height = height;

	/* Set the output window size. Only 1:1 scale is supported so far. */
	ret = reg_write16(client, REG_OUT_WIDTH_HIGH, width);
	if (!ret)
		ret = reg_write16(client, REG_OUT_HEIGHT_HIGH, height);

	/* Total width = output size + blanking */
	if (!ret)
		ret = reg_write16(client, REG_OUT_TOTAL_WIDTH_HIGH, total_width);
	if (!ret)
		ret = reg_write16(client, REG_OUT_TOTAL_HEIGHT_HIGH, total_height);

	/* Sets the window for AWB calculations */
	if (!ret)
		ret = reg_write16(client, REG_AVG_WINDOW_END_X_HIGH, width);
	if (!ret)
		ret = reg_write16(client, REG_AVG_WINDOW_END_Y_HIGH, height);

	return ret;
}