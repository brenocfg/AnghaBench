#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_subdev_desc {scalar_t__ drv_priv; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_8__ {TYPE_2__* ctrl_handler; } ;
struct ov772x_priv {int /*<<< orphan*/ * win; int /*<<< orphan*/ * cfmt; TYPE_2__ hdl; int /*<<< orphan*/  clk; TYPE_1__ subdev; scalar_t__ info; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  parent; } ;
struct i2c_client {TYPE_5__ dev; int /*<<< orphan*/  flags; } ;
struct i2c_adapter {TYPE_5__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLIENT_SCCB ; 
 int I2C_FUNC_PROTOCOL_MANGLING ; 
 int I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_BAND_STOP_FILTER ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 struct ov772x_priv* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int) ; 
 int /*<<< orphan*/ * ov772x_cfmts ; 
 int /*<<< orphan*/  ov772x_ctrl_ops ; 
 int /*<<< orphan*/  ov772x_subdev_ops ; 
 int ov772x_video_probe (struct ov772x_priv*) ; 
 int /*<<< orphan*/ * ov772x_win_sizes ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_clk_get (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov772x_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct ov772x_priv	*priv;
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct i2c_adapter	*adapter = to_i2c_adapter(client->dev.parent);
	int			ret;

	if (!ssdd || !ssdd->drv_priv) {
		dev_err(&client->dev, "OV772X: missing platform data!\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA |
					      I2C_FUNC_PROTOCOL_MANGLING)) {
		dev_err(&adapter->dev,
			"I2C-Adapter doesn't support SMBUS_BYTE_DATA or PROTOCOL_MANGLING\n");
		return -EIO;
	}
	client->flags |= I2C_CLIENT_SCCB;

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info = ssdd->drv_priv;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov772x_subdev_ops);
	v4l2_ctrl_handler_init(&priv->hdl, 3);
	v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
			V4L2_CID_BAND_STOP_FILTER, 0, 256, 1, 0);
	priv->subdev.ctrl_handler = &priv->hdl;
	if (priv->hdl.error)
		return priv->hdl.error;

	priv->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		goto eclkget;
	}

	ret = ov772x_video_probe(priv);
	if (ret < 0) {
		v4l2_clk_put(priv->clk);
eclkget:
		v4l2_ctrl_handler_free(&priv->hdl);
	} else {
		priv->cfmt = &ov772x_cfmts[0];
		priv->win = &ov772x_win_sizes[0];
	}

	return ret;
}