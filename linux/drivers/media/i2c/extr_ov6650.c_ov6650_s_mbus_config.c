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
struct v4l2_mbus_config {int flags; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMF_HREF_LOW ; 
 int /*<<< orphan*/  COMJ_PCLK_RISING ; 
 int /*<<< orphan*/  COMJ_VSYNC_HIGH ; 
 int /*<<< orphan*/  REG_COMF ; 
 int /*<<< orphan*/  REG_COMJ ; 
 int V4L2_MBUS_HSYNC_ACTIVE_LOW ; 
 int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 int ov6650_reg_rmw (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov6650_s_mbus_config(struct v4l2_subdev *sd,
				const struct v4l2_mbus_config *cfg)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	int ret;

	if (cfg->flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		ret = ov6650_reg_rmw(client, REG_COMJ, COMJ_PCLK_RISING, 0);
	else
		ret = ov6650_reg_rmw(client, REG_COMJ, 0, COMJ_PCLK_RISING);
	if (ret)
		return ret;

	if (cfg->flags & V4L2_MBUS_HSYNC_ACTIVE_LOW)
		ret = ov6650_reg_rmw(client, REG_COMF, COMF_HREF_LOW, 0);
	else
		ret = ov6650_reg_rmw(client, REG_COMF, 0, COMF_HREF_LOW);
	if (ret)
		return ret;

	if (cfg->flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		ret = ov6650_reg_rmw(client, REG_COMJ, COMJ_VSYNC_HIGH, 0);
	else
		ret = ov6650_reg_rmw(client, REG_COMJ, 0, COMJ_VSYNC_HIGH);

	return ret;
}