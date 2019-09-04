#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {TYPE_2__* ctrl_handler; int /*<<< orphan*/  flags; int /*<<< orphan*/ * internal_ops; int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {int error; } ;
struct TYPE_7__ {int /*<<< orphan*/  width; scalar_t__ left; int /*<<< orphan*/  height; scalar_t__ top; } ;
struct tvp5150 {int enable; TYPE_2__ hdl; TYPE_1__ rect; int /*<<< orphan*/  input; int /*<<< orphan*/  norm; int /*<<< orphan*/  mbus_type; struct v4l2_subdev sd; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_9__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_6__ dev; int /*<<< orphan*/  adapter; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONFIG_OF ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int I2C_FUNC_SMBUS_READ_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TVP5150_COMPOSITE1 ; 
 int /*<<< orphan*/  TVP5150_H_MAX ; 
 int /*<<< orphan*/  TVP5150_V_MAX_525_60 ; 
 int /*<<< orphan*/  TVP5150_V_MAX_OTHERS ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_PIXEL_RATE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  V4L2_MBUS_BT656 ; 
 int V4L2_STD_525_60 ; 
 int /*<<< orphan*/  V4L2_STD_ALL ; 
 int /*<<< orphan*/  V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int debug ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct tvp5150* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tvp5150_ctrl_ops ; 
 int tvp5150_detect_version (struct tvp5150*) ; 
 int tvp5150_init (struct i2c_client*) ; 
 int /*<<< orphan*/  tvp5150_internal_ops ; 
 int /*<<< orphan*/  tvp5150_log_status (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_ops ; 
 int tvp5150_parse_dt (struct tvp5150*,struct device_node*) ; 
 int tvp5150_read_std (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tvp5150_reset (struct v4l2_subdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tvp5150_test_patterns ; 
 int v4l2_async_register_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tvp5150_probe(struct i2c_client *c,
			 const struct i2c_device_id *id)
{
	struct tvp5150 *core;
	struct v4l2_subdev *sd;
	struct device_node *np = c->dev.of_node;
	int res;

	/* Check if the adapter supports the needed features */
	if (!i2c_check_functionality(c->adapter,
	     I2C_FUNC_SMBUS_READ_BYTE | I2C_FUNC_SMBUS_WRITE_BYTE_DATA))
		return -EIO;

	res = tvp5150_init(c);
	if (res)
		return res;

	core = devm_kzalloc(&c->dev, sizeof(*core), GFP_KERNEL);
	if (!core)
		return -ENOMEM;

	sd = &core->sd;

	if (IS_ENABLED(CONFIG_OF) && np) {
		res = tvp5150_parse_dt(core, np);
		if (res) {
			dev_err(sd->dev, "DT parsing error: %d\n", res);
			return res;
		}
	} else {
		/* Default to BT.656 embedded sync */
		core->mbus_type = V4L2_MBUS_BT656;
	}

	v4l2_i2c_subdev_init(sd, c, &tvp5150_ops);
	sd->internal_ops = &tvp5150_internal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;

#if defined(CONFIG_MEDIA_CONTROLLER)
	core->pads[DEMOD_PAD_IF_INPUT].flags = MEDIA_PAD_FL_SINK;
	core->pads[DEMOD_PAD_VID_OUT].flags = MEDIA_PAD_FL_SOURCE;
	core->pads[DEMOD_PAD_VBI_OUT].flags = MEDIA_PAD_FL_SOURCE;

	sd->entity.function = MEDIA_ENT_F_ATV_DECODER;

	res = media_entity_pads_init(&sd->entity, DEMOD_NUM_PADS, core->pads);
	if (res < 0)
		return res;

	sd->entity.ops = &tvp5150_sd_media_ops;
#endif

	res = tvp5150_detect_version(core);
	if (res < 0)
		return res;

	core->norm = V4L2_STD_ALL;	/* Default is autodetect */
	core->input = TVP5150_COMPOSITE1;
	core->enable = true;

	v4l2_ctrl_handler_init(&core->hdl, 5);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_SATURATION, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_HUE, -128, 127, 1, 0);
	v4l2_ctrl_new_std(&core->hdl, &tvp5150_ctrl_ops,
			V4L2_CID_PIXEL_RATE, 27000000,
			27000000, 1, 27000000);
	v4l2_ctrl_new_std_menu_items(&core->hdl, &tvp5150_ctrl_ops,
				     V4L2_CID_TEST_PATTERN,
				     ARRAY_SIZE(tvp5150_test_patterns) - 1,
				     0, 0, tvp5150_test_patterns);
	sd->ctrl_handler = &core->hdl;
	if (core->hdl.error) {
		res = core->hdl.error;
		goto err;
	}

	/* Default is no cropping */
	core->rect.top = 0;
	if (tvp5150_read_std(sd) & V4L2_STD_525_60)
		core->rect.height = TVP5150_V_MAX_525_60;
	else
		core->rect.height = TVP5150_V_MAX_OTHERS;
	core->rect.left = 0;
	core->rect.width = TVP5150_H_MAX;

	tvp5150_reset(sd, 0);	/* Calls v4l2_ctrl_handler_setup() */

	res = v4l2_async_register_subdev(sd);
	if (res < 0)
		goto err;

	if (debug > 1)
		tvp5150_log_status(sd);
	return 0;

err:
	v4l2_ctrl_handler_free(&core->hdl);
	return res;
}