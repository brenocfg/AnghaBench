#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int error; int /*<<< orphan*/ * lock; } ;
struct TYPE_8__ {int /*<<< orphan*/  entity; TYPE_2__* ctrl_handler; int /*<<< orphan*/  flags; } ;
struct ov2640_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; TYPE_2__ hdl; TYPE_1__ subdev; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_10__ {scalar_t__ of_node; int /*<<< orphan*/  parent; } ;
struct i2c_client {TYPE_6__ dev; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_6__*,char*) ; 
 struct ov2640_priv* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov2640_ctrl_ops ; 
 int ov2640_probe_dt (struct i2c_client*,struct ov2640_priv*) ; 
 int /*<<< orphan*/  ov2640_subdev_ops ; 
 int ov2640_video_probe (struct i2c_client*) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov2640_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct ov2640_priv	*priv;
	struct i2c_adapter	*adapter = to_i2c_adapter(client->dev.parent);
	int			ret;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&adapter->dev,
			"OV2640: I2C-Adapter doesn't support SMBUS\n");
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	if (client->dev.of_node) {
		priv->clk = devm_clk_get(&client->dev, "xvclk");
		if (IS_ERR(priv->clk))
			return PTR_ERR(priv->clk);
		ret = clk_prepare_enable(priv->clk);
		if (ret)
			return ret;
	}

	ret = ov2640_probe_dt(client, priv);
	if (ret)
		goto err_clk;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov2640_subdev_ops);
	priv->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	mutex_init(&priv->lock);
	v4l2_ctrl_handler_init(&priv->hdl, 2);
	priv->hdl.lock = &priv->lock;
	v4l2_ctrl_new_std(&priv->hdl, &ov2640_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov2640_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	priv->subdev.ctrl_handler = &priv->hdl;
	if (priv->hdl.error) {
		ret = priv->hdl.error;
		goto err_hdl;
	}
#if defined(CONFIG_MEDIA_CONTROLLER)
	priv->pad.flags = MEDIA_PAD_FL_SOURCE;
	priv->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&priv->subdev.entity, 1, &priv->pad);
	if (ret < 0)
		goto err_hdl;
#endif

	ret = ov2640_video_probe(client);
	if (ret < 0)
		goto err_videoprobe;

	ret = v4l2_async_register_subdev(&priv->subdev);
	if (ret < 0)
		goto err_videoprobe;

	dev_info(&adapter->dev, "OV2640 Probed\n");

	return 0;

err_videoprobe:
	media_entity_cleanup(&priv->subdev.entity);
err_hdl:
	v4l2_ctrl_handler_free(&priv->hdl);
	mutex_destroy(&priv->lock);
err_clk:
	clk_disable_unprepare(priv->clk);
	return ret;
}