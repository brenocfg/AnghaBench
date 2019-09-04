#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_subdev_desc {int dummy; } ;
struct TYPE_6__ {int error; } ;
struct TYPE_5__ {TYPE_2__* ctrl_handler; } ;
struct ov9740_priv {TYPE_2__ hdl; int /*<<< orphan*/  clk; TYPE_1__ subdev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct ov9740_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov9740_ctrl_ops ; 
 int /*<<< orphan*/  ov9740_subdev_ops ; 
 int ov9740_video_probe (struct i2c_client*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov9740_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct ov9740_priv *priv;
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	int ret;

	if (!ssdd) {
		dev_err(&client->dev, "Missing platform_data for driver\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov9740_subdev_ops);
	v4l2_ctrl_handler_init(&priv->hdl, 13);
	v4l2_ctrl_new_std(&priv->hdl, &ov9740_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov9740_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	priv->subdev.ctrl_handler = &priv->hdl;
	if (priv->hdl.error)
		return priv->hdl.error;

	priv->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		goto eclkget;
	}

	ret = ov9740_video_probe(client);
	if (ret < 0) {
		v4l2_clk_put(priv->clk);
eclkget:
		v4l2_ctrl_handler_free(&priv->hdl);
	}

	return ret;
}