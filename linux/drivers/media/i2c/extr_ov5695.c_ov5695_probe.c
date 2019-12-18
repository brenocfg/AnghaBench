#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  function; } ;
struct v4l2_subdev {TYPE_1__ entity; int /*<<< orphan*/  flags; int /*<<< orphan*/ * internal_ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct ov5695 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ctrl_handler; TYPE_2__ pad; struct v4l2_subdev subdev; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  xvclk; int /*<<< orphan*/ * cur_mode; struct i2c_client* client; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 scalar_t__ OV5695_XVCLK_FREQ ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  __ov5695_power_off (struct ov5695*) ; 
 int __ov5695_power_on (struct ov5695*) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ov5695* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_1__*) ; 
 int media_entity_pads_init (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov5695_check_sensor_id (struct ov5695*,struct i2c_client*) ; 
 int ov5695_configure_regulators (struct ov5695*) ; 
 int ov5695_initialize_controls (struct ov5695*) ; 
 int /*<<< orphan*/  ov5695_internal_ops ; 
 int /*<<< orphan*/  ov5695_subdev_ops ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/ * supported_modes ; 
 int v4l2_async_register_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov5695_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ov5695 *ov5695;
	struct v4l2_subdev *sd;
	int ret;

	ov5695 = devm_kzalloc(dev, sizeof(*ov5695), GFP_KERNEL);
	if (!ov5695)
		return -ENOMEM;

	ov5695->client = client;
	ov5695->cur_mode = &supported_modes[0];

	ov5695->xvclk = devm_clk_get(dev, "xvclk");
	if (IS_ERR(ov5695->xvclk)) {
		dev_err(dev, "Failed to get xvclk\n");
		return -EINVAL;
	}
	ret = clk_set_rate(ov5695->xvclk, OV5695_XVCLK_FREQ);
	if (ret < 0) {
		dev_err(dev, "Failed to set xvclk rate (24MHz)\n");
		return ret;
	}
	if (clk_get_rate(ov5695->xvclk) != OV5695_XVCLK_FREQ)
		dev_warn(dev, "xvclk mismatched, modes are based on 24MHz\n");

	ov5695->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ov5695->reset_gpio)) {
		dev_err(dev, "Failed to get reset-gpios\n");
		return -EINVAL;
	}

	ret = ov5695_configure_regulators(ov5695);
	if (ret) {
		dev_err(dev, "Failed to get power regulators\n");
		return ret;
	}

	mutex_init(&ov5695->mutex);

	sd = &ov5695->subdev;
	v4l2_i2c_subdev_init(sd, client, &ov5695_subdev_ops);
	ret = ov5695_initialize_controls(ov5695);
	if (ret)
		goto err_destroy_mutex;

	ret = __ov5695_power_on(ov5695);
	if (ret)
		goto err_free_handler;

	ret = ov5695_check_sensor_id(ov5695, client);
	if (ret)
		goto err_power_off;

#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	sd->internal_ops = &ov5695_internal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
#endif
#if defined(CONFIG_MEDIA_CONTROLLER)
	ov5695->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &ov5695->pad);
	if (ret < 0)
		goto err_power_off;
#endif

	ret = v4l2_async_register_subdev(sd);
	if (ret) {
		dev_err(dev, "v4l2 async register subdev failed\n");
		goto err_clean_entity;
	}

	pm_runtime_set_active(dev);
	pm_runtime_enable(dev);
	pm_runtime_idle(dev);

	return 0;

err_clean_entity:
#if defined(CONFIG_MEDIA_CONTROLLER)
	media_entity_cleanup(&sd->entity);
#endif
err_power_off:
	__ov5695_power_off(ov5695);
err_free_handler:
	v4l2_ctrl_handler_free(&ov5695->ctrl_handler);
err_destroy_mutex:
	mutex_destroy(&ov5695->mutex);

	return ret;
}