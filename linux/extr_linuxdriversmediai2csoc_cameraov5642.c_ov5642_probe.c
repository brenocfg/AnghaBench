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
struct soc_camera_subdev_desc {int dummy; } ;
struct TYPE_2__ {int width; int height; int left; int top; } ;
struct ov5642 {int total_width; int /*<<< orphan*/  clk; int /*<<< orphan*/  total_height; TYPE_1__ crop_rect; int /*<<< orphan*/ * fmt; int /*<<< orphan*/  subdev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BLANKING_EXTRA_WIDTH ; 
 int /*<<< orphan*/  BLANKING_MIN_HEIGHT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int OV5642_DEFAULT_HEIGHT ; 
 int OV5642_DEFAULT_WIDTH ; 
 int OV5642_MAX_HEIGHT ; 
 int OV5642_MAX_WIDTH ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ov5642* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ov5642_colour_fmts ; 
 int /*<<< orphan*/  ov5642_subdev_ops ; 
 int ov5642_video_probe (struct i2c_client*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov5642_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct ov5642 *priv;
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	int ret;

	if (!ssdd) {
		dev_err(&client->dev, "OV5642: missing platform data!\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(&client->dev, sizeof(struct ov5642), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov5642_subdev_ops);

	priv->fmt		= &ov5642_colour_fmts[0];

	priv->crop_rect.width	= OV5642_DEFAULT_WIDTH;
	priv->crop_rect.height	= OV5642_DEFAULT_HEIGHT;
	priv->crop_rect.left	= (OV5642_MAX_WIDTH - OV5642_DEFAULT_WIDTH) / 2;
	priv->crop_rect.top	= (OV5642_MAX_HEIGHT - OV5642_DEFAULT_HEIGHT) / 2;
	priv->total_width = OV5642_DEFAULT_WIDTH + BLANKING_EXTRA_WIDTH;
	priv->total_height = BLANKING_MIN_HEIGHT;

	priv->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	ret = ov5642_video_probe(client);
	if (ret < 0)
		v4l2_clk_put(priv->clk);

	return ret;
}