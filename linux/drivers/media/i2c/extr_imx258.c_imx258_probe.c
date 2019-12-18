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
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  function; } ;
struct TYPE_6__ {TYPE_3__ entity; int /*<<< orphan*/  flags; int /*<<< orphan*/ * internal_ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct imx258 {TYPE_1__ sd; TYPE_4__ pad; int /*<<< orphan*/ * cur_mode; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int device_property_read_u32 (int /*<<< orphan*/ *,char*,int*) ; 
 struct imx258* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imx258_free_controls (struct imx258*) ; 
 int imx258_identify_module (struct imx258*) ; 
 int imx258_init_controls (struct imx258*) ; 
 int /*<<< orphan*/  imx258_internal_ops ; 
 int /*<<< orphan*/  imx258_subdev_ops ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * supported_modes ; 
 int v4l2_async_register_subdev_sensor_common (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx258_probe(struct i2c_client *client)
{
	struct imx258 *imx258;
	int ret;
	u32 val = 0;

	device_property_read_u32(&client->dev, "clock-frequency", &val);
	if (val != 19200000)
		return -EINVAL;

	/*
	 * Check that the device is mounted upside down. The driver only
	 * supports a single pixel order right now.
	 */
	ret = device_property_read_u32(&client->dev, "rotation", &val);
	if (ret || val != 180)
		return -EINVAL;

	imx258 = devm_kzalloc(&client->dev, sizeof(*imx258), GFP_KERNEL);
	if (!imx258)
		return -ENOMEM;

	/* Initialize subdev */
	v4l2_i2c_subdev_init(&imx258->sd, client, &imx258_subdev_ops);

	/* Check module identity */
	ret = imx258_identify_module(imx258);
	if (ret)
		return ret;

	/* Set default mode to max resolution */
	imx258->cur_mode = &supported_modes[0];

	ret = imx258_init_controls(imx258);
	if (ret)
		return ret;

	/* Initialize subdev */
	imx258->sd.internal_ops = &imx258_internal_ops;
	imx258->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
	imx258->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	/* Initialize source pad */
	imx258->pad.flags = MEDIA_PAD_FL_SOURCE;

	ret = media_entity_pads_init(&imx258->sd.entity, 1, &imx258->pad);
	if (ret)
		goto error_handler_free;

	ret = v4l2_async_register_subdev_sensor_common(&imx258->sd);
	if (ret < 0)
		goto error_media_entity;

	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);
	pm_runtime_idle(&client->dev);

	return 0;

error_media_entity:
	media_entity_cleanup(&imx258->sd.entity);

error_handler_free:
	imx258_free_controls(imx258);

	return ret;
}