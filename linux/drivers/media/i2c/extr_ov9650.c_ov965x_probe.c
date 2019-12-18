#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  function; } ;
struct v4l2_subdev {int flags; TYPE_1__ entity; int /*<<< orphan*/  ctrl_handler; int /*<<< orphan*/ * internal_ops; int /*<<< orphan*/  name; } ;
struct regmap_config {int reg_bits; int val_bits; int max_register; } ;
struct TYPE_9__ {int /*<<< orphan*/  flags; } ;
struct ov965x {scalar_t__ mclk_frequency; int /*<<< orphan*/  lock; int /*<<< orphan*/ * fiv; int /*<<< orphan*/ * frame_size; int /*<<< orphan*/  format; TYPE_2__ pad; struct v4l2_subdev sd; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct ov9650_platform_data {scalar_t__ mclk_frequency; } ;
struct TYPE_10__ {struct ov9650_platform_data* platform_data; } ;
struct i2c_client {TYPE_4__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 scalar_t__ clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 scalar_t__ dev_fwnode (TYPE_4__*) ; 
 int /*<<< orphan*/  devm_clk_get (TYPE_4__*,int /*<<< orphan*/ *) ; 
 struct ov965x* devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_sccb (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_1__*) ; 
 int media_entity_pads_init (TYPE_1__*,int,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int ov965x_configure_gpios (struct ov965x*) ; 
 int ov965x_configure_gpios_pdata (struct ov965x*,struct ov9650_platform_data const*) ; 
 int ov965x_detect_sensor (struct v4l2_subdev*) ; 
 int /*<<< orphan*/ * ov965x_framesizes ; 
 int /*<<< orphan*/  ov965x_get_default_format (int /*<<< orphan*/ *) ; 
 int ov965x_initialize_controls (struct ov965x*) ; 
 int /*<<< orphan*/ * ov965x_intervals ; 
 int /*<<< orphan*/  ov965x_sd_internal_ops ; 
 int /*<<< orphan*/  ov965x_subdev_ops ; 
 int /*<<< orphan*/  ov965x_update_exposure_ctrl (struct ov965x*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int v4l2_async_register_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov965x_probe(struct i2c_client *client)
{
	const struct ov9650_platform_data *pdata = client->dev.platform_data;
	struct v4l2_subdev *sd;
	struct ov965x *ov965x;
	int ret;
	static const struct regmap_config ov965x_regmap_config = {
		.reg_bits = 8,
		.val_bits = 8,
		.max_register = 0xab,
	};

	ov965x = devm_kzalloc(&client->dev, sizeof(*ov965x), GFP_KERNEL);
	if (!ov965x)
		return -ENOMEM;

	ov965x->regmap = devm_regmap_init_sccb(client, &ov965x_regmap_config);
	if (IS_ERR(ov965x->regmap)) {
		dev_err(&client->dev, "Failed to allocate register map\n");
		return PTR_ERR(ov965x->regmap);
	}

	if (pdata) {
		if (pdata->mclk_frequency == 0) {
			dev_err(&client->dev, "MCLK frequency not specified\n");
			return -EINVAL;
		}
		ov965x->mclk_frequency = pdata->mclk_frequency;

		ret = ov965x_configure_gpios_pdata(ov965x, pdata);
		if (ret < 0)
			return ret;
	} else if (dev_fwnode(&client->dev)) {
		ov965x->clk = devm_clk_get(&client->dev, NULL);
		if (IS_ERR(ov965x->clk))
			return PTR_ERR(ov965x->clk);
		ov965x->mclk_frequency = clk_get_rate(ov965x->clk);

		ret = ov965x_configure_gpios(ov965x);
		if (ret < 0)
			return ret;
	} else {
		dev_err(&client->dev,
			"Neither platform data nor device property specified\n");

		return -EINVAL;
	}

	mutex_init(&ov965x->lock);

	sd = &ov965x->sd;
	v4l2_i2c_subdev_init(sd, client, &ov965x_subdev_ops);
	strscpy(sd->name, DRIVER_NAME, sizeof(sd->name));

	sd->internal_ops = &ov965x_sd_internal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
		     V4L2_SUBDEV_FL_HAS_EVENTS;

	ov965x->pad.flags = MEDIA_PAD_FL_SOURCE;
	sd->entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&sd->entity, 1, &ov965x->pad);
	if (ret < 0)
		goto err_mutex;

	ret = ov965x_initialize_controls(ov965x);
	if (ret < 0)
		goto err_me;

	ov965x_get_default_format(&ov965x->format);
	ov965x->frame_size = &ov965x_framesizes[0];
	ov965x->fiv = &ov965x_intervals[0];

	ret = ov965x_detect_sensor(sd);
	if (ret < 0)
		goto err_ctrls;

	/* Update exposure time min/max to match frame format */
	ov965x_update_exposure_ctrl(ov965x);

	ret = v4l2_async_register_subdev(sd);
	if (ret < 0)
		goto err_ctrls;

	return 0;
err_ctrls:
	v4l2_ctrl_handler_free(sd->ctrl_handler);
err_me:
	media_entity_cleanup(&sd->entity);
err_mutex:
	mutex_destroy(&ov965x->lock);
	return ret;
}