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
struct TYPE_7__ {int /*<<< orphan*/  function; int /*<<< orphan*/ * ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  ctrl_handler; TYPE_3__ entity; int /*<<< orphan*/  flags; int /*<<< orphan*/ * internal_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct ov5675 {int /*<<< orphan*/  mutex; TYPE_1__ sd; TYPE_4__ pad; int /*<<< orphan*/ * cur_mode; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ov5675* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov5675_check_hwcfg (int /*<<< orphan*/ *) ; 
 int ov5675_identify_module (struct ov5675*) ; 
 int ov5675_init_controls (struct ov5675*) ; 
 int /*<<< orphan*/  ov5675_internal_ops ; 
 int /*<<< orphan*/  ov5675_subdev_entity_ops ; 
 int /*<<< orphan*/  ov5675_subdev_ops ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * supported_modes ; 
 int v4l2_async_register_subdev_sensor_common (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov5675_probe(struct i2c_client *client)
{
	struct ov5675 *ov5675;
	int ret;

	ret = ov5675_check_hwcfg(&client->dev);
	if (ret) {
		dev_err(&client->dev, "failed to check HW configuration: %d",
			ret);
		return ret;
	}

	ov5675 = devm_kzalloc(&client->dev, sizeof(*ov5675), GFP_KERNEL);
	if (!ov5675)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&ov5675->sd, client, &ov5675_subdev_ops);
	ret = ov5675_identify_module(ov5675);
	if (ret) {
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		return ret;
	}

	mutex_init(&ov5675->mutex);
	ov5675->cur_mode = &supported_modes[0];
	ret = ov5675_init_controls(ov5675);
	if (ret) {
		dev_err(&client->dev, "failed to init controls: %d", ret);
		goto probe_error_v4l2_ctrl_handler_free;
	}

	ov5675->sd.internal_ops = &ov5675_internal_ops;
	ov5675->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov5675->sd.entity.ops = &ov5675_subdev_entity_ops;
	ov5675->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ov5675->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&ov5675->sd.entity, 1, &ov5675->pad);
	if (ret) {
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		goto probe_error_v4l2_ctrl_handler_free;
	}

	ret = v4l2_async_register_subdev_sensor_common(&ov5675->sd);
	if (ret < 0) {
		dev_err(&client->dev, "failed to register V4L2 subdev: %d",
			ret);
		goto probe_error_media_entity_cleanup;
	}

	/*
	 * Device is already turned on by i2c-core with ACPI domain PM.
	 * Enable runtime PM and turn off the device.
	 */
	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);
	pm_runtime_idle(&client->dev);

	return 0;

probe_error_media_entity_cleanup:
	media_entity_cleanup(&ov5675->sd.entity);

probe_error_v4l2_ctrl_handler_free:
	v4l2_ctrl_handler_free(ov5675->sd.ctrl_handler);
	mutex_destroy(&ov5675->mutex);

	return ret;
}