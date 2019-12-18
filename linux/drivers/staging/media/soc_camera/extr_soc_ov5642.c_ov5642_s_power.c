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
struct soc_camera_subdev_desc {int dummy; } ;
struct ov5642 {int /*<<< orphan*/  clk; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ov5642_default_regs_finalise ; 
 int /*<<< orphan*/  ov5642_default_regs_init ; 
 int ov5642_set_resolution (struct v4l2_subdev*) ; 
 int ov5642_write_array (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int soc_camera_power_off (int /*<<< orphan*/ *,struct soc_camera_subdev_desc*,int /*<<< orphan*/ ) ; 
 int soc_camera_power_on (int /*<<< orphan*/ *,struct soc_camera_subdev_desc*,int /*<<< orphan*/ ) ; 
 struct ov5642* to_ov5642 (struct i2c_client*) ; 
 struct i2c_client* v4l2_get_subdevdata (struct v4l2_subdev*) ; 

__attribute__((used)) static int ov5642_s_power(struct v4l2_subdev *sd, int on)
{
	struct i2c_client *client = v4l2_get_subdevdata(sd);
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct ov5642 *priv = to_ov5642(client);
	int ret;

	if (!on)
		return soc_camera_power_off(&client->dev, ssdd, priv->clk);

	ret = soc_camera_power_on(&client->dev, ssdd, priv->clk);
	if (ret < 0)
		return ret;

	ret = ov5642_write_array(client, ov5642_default_regs_init);
	if (!ret)
		ret = ov5642_set_resolution(sd);
	if (!ret)
		ret = ov5642_write_array(client, ov5642_default_regs_finalise);

	return ret;
}