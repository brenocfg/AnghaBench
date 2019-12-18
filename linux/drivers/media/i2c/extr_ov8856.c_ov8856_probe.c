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
struct ov8856 {int /*<<< orphan*/  mutex; TYPE_1__ sd; TYPE_4__ pad; int /*<<< orphan*/ * cur_mode; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct ov8856* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov8856_check_hwcfg (int /*<<< orphan*/ *) ; 
 int ov8856_identify_module (struct ov8856*) ; 
 int ov8856_init_controls (struct ov8856*) ; 
 int /*<<< orphan*/  ov8856_internal_ops ; 
 int /*<<< orphan*/  ov8856_subdev_entity_ops ; 
 int /*<<< orphan*/  ov8856_subdev_ops ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * supported_modes ; 
 int v4l2_async_register_subdev_sensor_common (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov8856_probe(struct i2c_client *client)
{
	struct ov8856 *ov8856;
	int ret;

	ret = ov8856_check_hwcfg(&client->dev);
	if (ret) {
		dev_err(&client->dev, "failed to check HW configuration: %d",
			ret);
		return ret;
	}

	ov8856 = devm_kzalloc(&client->dev, sizeof(*ov8856), GFP_KERNEL);
	if (!ov8856)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&ov8856->sd, client, &ov8856_subdev_ops);
	ret = ov8856_identify_module(ov8856);
	if (ret) {
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		return ret;
	}

	mutex_init(&ov8856->mutex);
	ov8856->cur_mode = &supported_modes[0];
	ret = ov8856_init_controls(ov8856);
	if (ret) {
		dev_err(&client->dev, "failed to init controls: %d", ret);
		goto probe_error_v4l2_ctrl_handler_free;
	}

	ov8856->sd.internal_ops = &ov8856_internal_ops;
	ov8856->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	ov8856->sd.entity.ops = &ov8856_subdev_entity_ops;
	ov8856->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ov8856->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&ov8856->sd.entity, 1, &ov8856->pad);
	if (ret) {
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		goto probe_error_v4l2_ctrl_handler_free;
	}

	ret = v4l2_async_register_subdev_sensor_common(&ov8856->sd);
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
	media_entity_cleanup(&ov8856->sd.entity);

probe_error_v4l2_ctrl_handler_free:
	v4l2_ctrl_handler_free(ov8856->sd.ctrl_handler);
	mutex_destroy(&ov8856->mutex);

	return ret;
}