#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int error; int /*<<< orphan*/ * lock; } ;
struct TYPE_11__ {int /*<<< orphan*/  entity; TYPE_2__* ctrl_handler; int /*<<< orphan*/  flags; } ;
struct ov772x_priv {int fps; int /*<<< orphan*/  lock; TYPE_2__ hdl; scalar_t__ clk; scalar_t__ pwdn_gpio; TYPE_1__ subdev; int /*<<< orphan*/ * win; int /*<<< orphan*/ * cfmt; void* band_filter_ctrl; void* hflip_ctrl; void* vflip_ctrl; scalar_t__ info; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {scalar_t__ platform_data; int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_6__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {TYPE_6__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  V4L2_CID_BAND_STOP_FILTER ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 scalar_t__ clk_get (TYPE_6__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_6__*,char*) ; 
 struct ov772x_priv* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ gpiod_get_optional (TYPE_6__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ov772x_cfmts ; 
 int /*<<< orphan*/  ov772x_ctrl_ops ; 
 int /*<<< orphan*/  ov772x_subdev_ops ; 
 int ov772x_video_probe (struct ov772x_priv*) ; 
 int /*<<< orphan*/ * ov772x_win_sizes ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 void* v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov772x_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct ov772x_priv	*priv;
	struct i2c_adapter	*adapter = client->adapter;
	int			ret;

	if (!client->dev.of_node && !client->dev.platform_data) {
		dev_err(&client->dev,
			"Missing ov772x platform data for non-DT device\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&adapter->dev,
			"I2C-Adapter doesn't support SMBUS_BYTE_DATA\n");
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info = client->dev.platform_data;
	mutex_init(&priv->lock);

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov772x_subdev_ops);
	priv->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	v4l2_ctrl_handler_init(&priv->hdl, 3);
	/* Use our mutex for the controls */
	priv->hdl.lock = &priv->lock;
	priv->vflip_ctrl = v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
					     V4L2_CID_VFLIP, 0, 1, 1, 0);
	priv->hflip_ctrl = v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
					     V4L2_CID_HFLIP, 0, 1, 1, 0);
	priv->band_filter_ctrl = v4l2_ctrl_new_std(&priv->hdl, &ov772x_ctrl_ops,
						   V4L2_CID_BAND_STOP_FILTER,
						   0, 256, 1, 0);
	priv->subdev.ctrl_handler = &priv->hdl;
	if (priv->hdl.error) {
		ret = priv->hdl.error;
		goto error_mutex_destroy;
	}

	priv->clk = clk_get(&client->dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(&client->dev, "Unable to get xclk clock\n");
		ret = PTR_ERR(priv->clk);
		goto error_ctrl_free;
	}

	priv->pwdn_gpio = gpiod_get_optional(&client->dev, "powerdown",
					     GPIOD_OUT_LOW);
	if (IS_ERR(priv->pwdn_gpio)) {
		dev_info(&client->dev, "Unable to get GPIO \"powerdown\"");
		ret = PTR_ERR(priv->pwdn_gpio);
		goto error_clk_put;
	}

	ret = ov772x_video_probe(priv);
	if (ret < 0)
		goto error_gpio_put;

#ifdef CONFIG_MEDIA_CONTROLLER
	priv->pad.flags = MEDIA_PAD_FL_SOURCE;
	priv->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&priv->subdev.entity, 1, &priv->pad);
	if (ret < 0)
		goto error_gpio_put;
#endif

	priv->cfmt = &ov772x_cfmts[0];
	priv->win = &ov772x_win_sizes[0];
	priv->fps = 15;

	ret = v4l2_async_register_subdev(&priv->subdev);
	if (ret)
		goto error_entity_cleanup;

	return 0;

error_entity_cleanup:
	media_entity_cleanup(&priv->subdev.entity);
error_gpio_put:
	if (priv->pwdn_gpio)
		gpiod_put(priv->pwdn_gpio);
error_clk_put:
	clk_put(priv->clk);
error_ctrl_free:
	v4l2_ctrl_handler_free(&priv->hdl);
error_mutex_destroy:
	mutex_destroy(&priv->lock);

	return ret;
}