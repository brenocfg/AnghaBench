#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  function; } ;
struct v4l2_subdev {int flags; TYPE_1__ entity; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/ * internal_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
struct ov7740 {struct v4l2_subdev subdev; int /*<<< orphan*/  format; int /*<<< orphan*/ * frmsize; int /*<<< orphan*/ * fmt; int /*<<< orphan*/  mutex; TYPE_2__ pad; int /*<<< orphan*/  regmap; int /*<<< orphan*/  xvclk; } ;
struct i2c_client {int addr; int /*<<< orphan*/  dev; TYPE_4__* adapter; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_CLIENT_SCCB ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct ov7740* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_1__*) ; 
 int media_entity_pads_init (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov7740_detect (struct ov7740*) ; 
 int /*<<< orphan*/ * ov7740_formats ; 
 int /*<<< orphan*/ * ov7740_framesizes ; 
 int /*<<< orphan*/  ov7740_free_controls (struct ov7740*) ; 
 int /*<<< orphan*/  ov7740_get_default_format (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7740_init_controls (struct ov7740*) ; 
 int ov7740_probe_dt (struct i2c_client*,struct ov7740*) ; 
 int /*<<< orphan*/  ov7740_regmap_config ; 
 int ov7740_set_power (struct ov7740*,int) ; 
 int /*<<< orphan*/  ov7740_subdev_internal_ops ; 
 int /*<<< orphan*/  ov7740_subdev_ops ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov7740_probe(struct i2c_client *client)
{
	struct ov7740 *ov7740;
	struct v4l2_subdev *sd;
	int ret;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev,
			"OV7740: I2C-Adapter doesn't support SMBUS\n");
		return -EIO;
	}

	ov7740 = devm_kzalloc(&client->dev, sizeof(*ov7740), GFP_KERNEL);
	if (!ov7740)
		return -ENOMEM;

	ov7740->xvclk = devm_clk_get(&client->dev, "xvclk");
	if (IS_ERR(ov7740->xvclk)) {
		ret = PTR_ERR(ov7740->xvclk);
		dev_err(&client->dev,
			"OV7740: fail to get xvclk: %d\n", ret);
		return ret;
	}

	ret = ov7740_probe_dt(client, ov7740);
	if (ret)
		return ret;

	ov7740->regmap = devm_regmap_init_i2c(client, &ov7740_regmap_config);
	if (IS_ERR(ov7740->regmap)) {
		ret = PTR_ERR(ov7740->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	sd = &ov7740->subdev;
	client->flags |= I2C_CLIENT_SCCB;
	v4l2_i2c_subdev_init(sd, client, &ov7740_subdev_ops);

#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	sd->internal_ops = &ov7740_subdev_internal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
#endif

#if defined(CONFIG_MEDIA_CONTROLLER)
	ov7740->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &ov7740->pad);
	if (ret)
		return ret;
#endif

	ret = ov7740_set_power(ov7740, 1);
	if (ret)
		return ret;

	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);

	ret = ov7740_detect(ov7740);
	if (ret)
		goto error_detect;

	mutex_init(&ov7740->mutex);

	ret = ov7740_init_controls(ov7740);
	if (ret)
		goto error_init_controls;

	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	ov7740->fmt = &ov7740_formats[0];
	ov7740->frmsize = &ov7740_framesizes[0];

	ov7740_get_default_format(sd, &ov7740->format);

	ret = v4l2_async_register_subdev(sd);
	if (ret)
		goto error_async_register;

	pm_runtime_idle(&client->dev);

	return 0;

error_async_register:
	v4l2_ctrl_handler_free(ov7740->subdev.ctrl_handler);
error_init_controls:
	ov7740_free_controls(ov7740);
error_detect:
	pm_runtime_disable(&client->dev);
	pm_runtime_set_suspended(&client->dev);
	ov7740_set_power(ov7740, 0);
	media_entity_cleanup(&ov7740->subdev.entity);

	return ret;
}