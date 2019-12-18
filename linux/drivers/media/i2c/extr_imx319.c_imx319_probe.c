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
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_8__ {int /*<<< orphan*/  function; int /*<<< orphan*/ * ops; } ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  ctrl_handler; TYPE_3__ entity; int /*<<< orphan*/ * internal_ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct imx319 {scalar_t__ link_def_freq; int /*<<< orphan*/  mutex; TYPE_1__ sd; TYPE_4__ pad; int /*<<< orphan*/ * cur_mode; TYPE_6__* hwcfg; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {size_t nr_of_link_freqs; scalar_t__* link_freqs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IMX319_LINK_FREQ_INDEX ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct imx319* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 TYPE_6__* imx319_get_hwcfg (int /*<<< orphan*/ *) ; 
 int imx319_identify_module (struct imx319*) ; 
 int imx319_init_controls (struct imx319*) ; 
 int /*<<< orphan*/  imx319_internal_ops ; 
 int /*<<< orphan*/  imx319_subdev_entity_ops ; 
 int /*<<< orphan*/  imx319_subdev_ops ; 
 scalar_t__* link_freq_menu_items ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_3__*) ; 
 int media_entity_pads_init (TYPE_3__*,int,TYPE_4__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_idle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_set_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * supported_modes ; 
 int v4l2_async_register_subdev_sensor_common (TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_1__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx319_probe(struct i2c_client *client)
{
	struct imx319 *imx319;
	int ret;
	u32 i;

	imx319 = devm_kzalloc(&client->dev, sizeof(*imx319), GFP_KERNEL);
	if (!imx319)
		return -ENOMEM;

	mutex_init(&imx319->mutex);

	/* Initialize subdev */
	v4l2_i2c_subdev_init(&imx319->sd, client, &imx319_subdev_ops);

	/* Check module identity */
	ret = imx319_identify_module(imx319);
	if (ret) {
		dev_err(&client->dev, "failed to find sensor: %d", ret);
		goto error_probe;
	}

	imx319->hwcfg = imx319_get_hwcfg(&client->dev);
	if (!imx319->hwcfg) {
		dev_err(&client->dev, "failed to get hwcfg");
		ret = -ENODEV;
		goto error_probe;
	}

	imx319->link_def_freq = link_freq_menu_items[IMX319_LINK_FREQ_INDEX];
	for (i = 0; i < imx319->hwcfg->nr_of_link_freqs; i++) {
		if (imx319->hwcfg->link_freqs[i] == imx319->link_def_freq) {
			dev_dbg(&client->dev, "link freq index %d matched", i);
			break;
		}
	}

	if (i == imx319->hwcfg->nr_of_link_freqs) {
		dev_err(&client->dev, "no link frequency supported");
		ret = -EINVAL;
		goto error_probe;
	}

	/* Set default mode to max resolution */
	imx319->cur_mode = &supported_modes[0];

	ret = imx319_init_controls(imx319);
	if (ret) {
		dev_err(&client->dev, "failed to init controls: %d", ret);
		goto error_probe;
	}

	/* Initialize subdev */
	imx319->sd.internal_ops = &imx319_internal_ops;
	imx319->sd.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
		V4L2_SUBDEV_FL_HAS_EVENTS;
	imx319->sd.entity.ops = &imx319_subdev_entity_ops;
	imx319->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;

	/* Initialize source pad */
	imx319->pad.flags = MEDIA_PAD_FL_SOURCE;
	ret = media_entity_pads_init(&imx319->sd.entity, 1, &imx319->pad);
	if (ret) {
		dev_err(&client->dev, "failed to init entity pads: %d", ret);
		goto error_handler_free;
	}

	ret = v4l2_async_register_subdev_sensor_common(&imx319->sd);
	if (ret < 0)
		goto error_media_entity;

	/*
	 * Device is already turned on by i2c-core with ACPI domain PM.
	 * Enable runtime PM and turn off the device.
	 */
	pm_runtime_set_active(&client->dev);
	pm_runtime_enable(&client->dev);
	pm_runtime_idle(&client->dev);

	return 0;

error_media_entity:
	media_entity_cleanup(&imx319->sd.entity);

error_handler_free:
	v4l2_ctrl_handler_free(imx319->sd.ctrl_handler);

error_probe:
	mutex_destroy(&imx319->mutex);

	return ret;
}