#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct TYPE_6__ {TYPE_3__ entity; int /*<<< orphan*/  flags; int /*<<< orphan*/ * internal_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct ov2685 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ctrl_handler; TYPE_1__ subdev; TYPE_4__ pad; int /*<<< orphan*/  reset_gpio; int /*<<< orphan*/  xvclk; int /*<<< orphan*/ * cur_mode; struct i2c_client* client; } ;
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
 scalar_t__ OV2685_XVCLK_FREQ ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  __ov2685_power_off (struct ov2685*) ; 
 int __ov2685_power_on (struct ov2685*) ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ov2685* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov2685_check_sensor_id (struct ov2685*,struct i2c_client*) ; 
 int ov2685_configure_regulators (struct ov2685*) ; 
 int ov2685_initialize_controls (struct ov2685*) ; 
 int /*<<< orphan*/  ov2685_internal_ops ; 
 int /*<<< orphan*/  ov2685_subdev_ops ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_idle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (struct device*) ; 
 int /*<<< orphan*/ * supported_modes ; 
 int v4l2_async_register_subdev (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov2685_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct device *dev = &client->dev;
	struct ov2685 *ov2685;
	int ret;

	ov2685 = devm_kzalloc(dev, sizeof(*ov2685), GFP_KERNEL);
	if (!ov2685)
		return -ENOMEM;

	ov2685->client = client;
	ov2685->cur_mode = &supported_modes[0];

	ov2685->xvclk = devm_clk_get(dev, "xvclk");
	if (IS_ERR(ov2685->xvclk)) {
		dev_err(dev, "Failed to get xvclk\n");
		return -EINVAL;
	}
	ret = clk_set_rate(ov2685->xvclk, OV2685_XVCLK_FREQ);
	if (ret < 0) {
		dev_err(dev, "Failed to set xvclk rate (24MHz)\n");
		return ret;
	}
	if (clk_get_rate(ov2685->xvclk) != OV2685_XVCLK_FREQ)
		dev_warn(dev, "xvclk mismatched, modes are based on 24MHz\n");

	ov2685->reset_gpio = devm_gpiod_get(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(ov2685->reset_gpio)) {
		dev_err(dev, "Failed to get reset-gpios\n");
		return -EINVAL;
	}

	ret = ov2685_configure_regulators(ov2685);
	if (ret) {
		dev_err(dev, "Failed to get power regulators\n");
		return ret;
	}

	mutex_init(&ov2685->mutex);
	v4l2_i2c_subdev_init(&ov2685->subdev, client, &ov2685_subdev_ops);
	ret = ov2685_initialize_controls(ov2685);
	if (ret)
		goto err_destroy_mutex;

	ret = __ov2685_power_on(ov2685);
	if (ret)
		goto err_free_handler;

	ret = ov2685_check_sensor_id(ov2685, client);
	if (ret)
		goto err_power_off;

#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	ov2685->subdev.internal_ops = &ov2685_internal_ops;
	ov2685->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
#endif
#if defined(CONFIG_MEDIA_CONTROLLER)
	ov2685->pad.flags = MEDIA_PAD_FL_SOURCE;
	ov2685->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&ov2685->subdev.entity, 1, &ov2685->pad);
	if (ret < 0)
		goto err_power_off;
#endif

	ret = v4l2_async_register_subdev(&ov2685->subdev);
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
	media_entity_cleanup(&ov2685->subdev.entity);
#endif
err_power_off:
	__ov2685_power_off(ov2685);
err_free_handler:
	v4l2_ctrl_handler_free(&ov2685->ctrl_handler);
err_destroy_mutex:
	mutex_destroy(&ov2685->mutex);

	return ret;
}