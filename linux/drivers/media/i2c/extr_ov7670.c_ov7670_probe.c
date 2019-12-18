#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  function; } ;
struct v4l2_subdev {int flags; TYPE_10__ entity; TYPE_2__* ctrl_handler; int /*<<< orphan*/ * internal_ops; } ;
struct v4l2_fract {int numerator; int denominator; } ;
struct TYPE_19__ {int error; } ;
struct TYPE_17__ {int /*<<< orphan*/  flags; } ;
struct ov7670_info {int clock_speed; int pll_bypass; int pclk_hb_disable; TYPE_2__ hdl; struct v4l2_subdev sd; TYPE_11__ pad; void* saturation; void* auto_exposure; void* auto_gain; void* exposure; void* gain; void* hue; TYPE_9__* devtype; scalar_t__ clkrc; int /*<<< orphan*/  format; int /*<<< orphan*/ * wsize; int /*<<< orphan*/ * fmt; int /*<<< orphan*/ * clk; int /*<<< orphan*/  use_smbus; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct ov7670_config {int clock_speed; scalar_t__ pclk_hb_disable; scalar_t__ pll_bypass; int /*<<< orphan*/  use_smbus; int /*<<< orphan*/  min_height; int /*<<< orphan*/  min_width; } ;
struct i2c_device_id {size_t driver_data; } ;
struct TYPE_20__ {struct ov7670_config* platform_data; } ;
struct i2c_client {int addr; TYPE_1__* adapter; TYPE_8__ dev; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* set_framerate ) (struct v4l2_subdev*,struct v4l2_fract*) ;int /*<<< orphan*/ * win_sizes; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_CID_AUTOGAIN ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_CONTRAST ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int clk_get_rate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug ; 
 scalar_t__ dev_fwnode (TYPE_8__*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_8__*,char*) ; 
 struct ov7670_info* devm_kzalloc (TYPE_8__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_10__*) ; 
 int media_entity_pads_init (TYPE_10__*,int,TYPE_11__*) ; 
 int /*<<< orphan*/  ov7670_ctrl_ops ; 
 int ov7670_detect (struct v4l2_subdev*) ; 
 TYPE_9__* ov7670_devdata ; 
 int /*<<< orphan*/ * ov7670_formats ; 
 int /*<<< orphan*/  ov7670_get_default_format (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 
 int ov7670_init_gpio (struct i2c_client*,struct ov7670_info*) ; 
 int /*<<< orphan*/  ov7670_ops ; 
 int ov7670_parse_dt (TYPE_8__*,struct ov7670_info*) ; 
 int /*<<< orphan*/  ov7670_power_off (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  ov7670_power_on (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  ov7670_subdev_internal_ops ; 
 int /*<<< orphan*/  ov7670_test_pattern_menu ; 
 int /*<<< orphan*/  stub1 (struct v4l2_subdev*,struct v4l2_fract*) ; 
 int v4l2_async_register_subdev (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_cluster (int,void**) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_2__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_setup (TYPE_2__*) ; 
 void* v4l2_ctrl_new_std (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 void* v4l2_ctrl_new_std_menu (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (struct v4l2_subdev*,struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l_dbg (int,int /*<<< orphan*/ ,struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l_info (struct i2c_client*,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov7670_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct v4l2_fract tpf;
	struct v4l2_subdev *sd;
	struct ov7670_info *info;
	int ret;

	info = devm_kzalloc(&client->dev, sizeof(*info), GFP_KERNEL);
	if (info == NULL)
		return -ENOMEM;
	sd = &info->sd;
	v4l2_i2c_subdev_init(sd, client, &ov7670_ops);

#ifdef CONFIG_VIDEO_V4L2_SUBDEV_API
	sd->internal_ops = &ov7670_subdev_internal_ops;
	sd->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE | V4L2_SUBDEV_FL_HAS_EVENTS;
#endif

	info->clock_speed = 30; /* default: a guess */

	if (dev_fwnode(&client->dev)) {
		ret = ov7670_parse_dt(&client->dev, info);
		if (ret)
			return ret;

	} else if (client->dev.platform_data) {
		struct ov7670_config *config = client->dev.platform_data;

		/*
		 * Must apply configuration before initializing device, because it
		 * selects I/O method.
		 */
		info->min_width = config->min_width;
		info->min_height = config->min_height;
		info->use_smbus = config->use_smbus;

		if (config->clock_speed)
			info->clock_speed = config->clock_speed;

		if (config->pll_bypass)
			info->pll_bypass = true;

		if (config->pclk_hb_disable)
			info->pclk_hb_disable = true;
	}

	info->clk = devm_clk_get(&client->dev, "xclk"); /* optional */
	if (IS_ERR(info->clk)) {
		ret = PTR_ERR(info->clk);
		if (ret == -ENOENT)
			info->clk = NULL;
		else
			return ret;
	}

	ret = ov7670_init_gpio(client, info);
	if (ret)
		return ret;

	ov7670_power_on(sd);

	if (info->clk) {
		info->clock_speed = clk_get_rate(info->clk) / 1000000;
		if (info->clock_speed < 10 || info->clock_speed > 48) {
			ret = -EINVAL;
			goto power_off;
		}
	}

	/* Make sure it's an ov7670 */
	ret = ov7670_detect(sd);
	if (ret) {
		v4l_dbg(1, debug, client,
			"chip found @ 0x%x (%s) is not an ov7670 chip.\n",
			client->addr << 1, client->adapter->name);
		goto power_off;
	}
	v4l_info(client, "chip found @ 0x%02x (%s)\n",
			client->addr << 1, client->adapter->name);

	info->devtype = &ov7670_devdata[id->driver_data];
	info->fmt = &ov7670_formats[0];
	info->wsize = &info->devtype->win_sizes[0];

	ov7670_get_default_format(sd, &info->format);

	info->clkrc = 0;

	/* Set default frame rate to 30 fps */
	tpf.numerator = 1;
	tpf.denominator = 30;
	info->devtype->set_framerate(sd, &tpf);

	v4l2_ctrl_handler_init(&info->hdl, 10);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 255, 1, 128);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_CONTRAST, 0, 127, 1, 64);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	info->saturation = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_SATURATION, 0, 256, 1, 128);
	info->hue = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_HUE, -180, 180, 5, 0);
	info->gain = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_GAIN, 0, 255, 1, 128);
	info->auto_gain = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	info->exposure = v4l2_ctrl_new_std(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 65535, 1, 500);
	info->auto_exposure = v4l2_ctrl_new_std_menu(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_EXPOSURE_AUTO, V4L2_EXPOSURE_MANUAL, 0,
			V4L2_EXPOSURE_AUTO);
	v4l2_ctrl_new_std_menu_items(&info->hdl, &ov7670_ctrl_ops,
			V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(ov7670_test_pattern_menu) - 1, 0, 0,
			ov7670_test_pattern_menu);
	sd->ctrl_handler = &info->hdl;
	if (info->hdl.error) {
		ret = info->hdl.error;

		goto hdl_free;
	}
	/*
	 * We have checked empirically that hw allows to read back the gain
	 * value chosen by auto gain but that's not the case for auto exposure.
	 */
	v4l2_ctrl_auto_cluster(2, &info->auto_gain, 0, true);
	v4l2_ctrl_auto_cluster(2, &info->auto_exposure,
			       V4L2_EXPOSURE_MANUAL, false);
	v4l2_ctrl_cluster(2, &info->saturation);

#if defined(CONFIG_MEDIA_CONTROLLER)
	info->pad.flags = MEDIA_PAD_FL_SOURCE;
	info->sd.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&info->sd.entity, 1, &info->pad);
	if (ret < 0)
		goto hdl_free;
#endif

	v4l2_ctrl_handler_setup(&info->hdl);

	ret = v4l2_async_register_subdev(&info->sd);
	if (ret < 0)
		goto entity_cleanup;

	ov7670_power_off(sd);
	return 0;

entity_cleanup:
	media_entity_cleanup(&info->sd.entity);
hdl_free:
	v4l2_ctrl_handler_free(&info->hdl);
power_off:
	ov7670_power_off(sd);
	return ret;
}