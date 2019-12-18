#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int error; } ;
struct TYPE_15__ {int /*<<< orphan*/  function; } ;
struct TYPE_19__ {int flags; TYPE_11__ entity; int /*<<< orphan*/ * dev; TYPE_4__* ctrl_handler; } ;
struct TYPE_18__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_17__ {int numerator; int /*<<< orphan*/  denominator; } ;
struct TYPE_16__ {int /*<<< orphan*/  flags; } ;
struct mt9m111 {int lastpage; int /*<<< orphan*/  clk; TYPE_4__ hdl; TYPE_3__ subdev; int /*<<< orphan*/  power_lock; int /*<<< orphan*/ * fmt; TYPE_2__ rect; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_10__* current_mode; TYPE_1__ frame_interval; TYPE_12__ pad; int /*<<< orphan*/  gain; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  regulator; } ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct TYPE_14__ {int /*<<< orphan*/  max_fps; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int BIT (int) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEDIA_ENT_F_CAM_SENSOR ; 
 int /*<<< orphan*/  MEDIA_PAD_FL_SOURCE ; 
 int /*<<< orphan*/  MT9M111_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9M111_MAX_WIDTH ; 
 int /*<<< orphan*/  MT9M111_MIN_DARK_COLS ; 
 int /*<<< orphan*/  MT9M111_MIN_DARK_ROWS ; 
 size_t MT9M111_MODE_SXGA_15FPS ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_COLORFX ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_TEST_PATTERN ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int V4L2_COLORFX_BW ; 
 int V4L2_COLORFX_NEGATIVE ; 
 int V4L2_COLORFX_NONE ; 
 int V4L2_COLORFX_SEPIA ; 
 int V4L2_COLORFX_SOLARIZATION ; 
 int V4L2_EXPOSURE_AUTO ; 
 int V4L2_SUBDEV_FL_HAS_DEVNODE ; 
 int V4L2_SUBDEV_FL_HAS_EVENTS ; 
 int /*<<< orphan*/  context_b ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ dev_fwnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct mt9m111* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_entity_cleanup (TYPE_11__*) ; 
 int media_entity_pads_init (TYPE_11__*,int,TYPE_12__*) ; 
 int /*<<< orphan*/ * mt9m111_colour_fmts ; 
 int /*<<< orphan*/  mt9m111_ctrl_ops ; 
 TYPE_10__* mt9m111_mode_data ; 
 int mt9m111_probe_fw (struct i2c_client*,struct mt9m111*) ; 
 int /*<<< orphan*/  mt9m111_subdev_ops ; 
 int /*<<< orphan*/  mt9m111_test_pattern_menu ; 
 int mt9m111_video_probe (struct i2c_client*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int v4l2_async_register_subdev (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_4__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu_items (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_3__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m111_probe(struct i2c_client *client)
{
	struct mt9m111 *mt9m111;
	struct i2c_adapter *adapter = client->adapter;
	int ret;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		return -EIO;
	}

	mt9m111 = devm_kzalloc(&client->dev, sizeof(struct mt9m111), GFP_KERNEL);
	if (!mt9m111)
		return -ENOMEM;

	if (dev_fwnode(&client->dev)) {
		ret = mt9m111_probe_fw(client, mt9m111);
		if (ret)
			return ret;
	}

	mt9m111->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(mt9m111->clk))
		return PTR_ERR(mt9m111->clk);

	mt9m111->regulator = devm_regulator_get(&client->dev, "vdd");
	if (IS_ERR(mt9m111->regulator)) {
		dev_err(&client->dev, "regulator not found: %ld\n",
			PTR_ERR(mt9m111->regulator));
		return PTR_ERR(mt9m111->regulator);
	}

	/* Default HIGHPOWER context */
	mt9m111->ctx = &context_b;

	v4l2_i2c_subdev_init(&mt9m111->subdev, client, &mt9m111_subdev_ops);
	mt9m111->subdev.flags |= V4L2_SUBDEV_FL_HAS_DEVNODE |
				 V4L2_SUBDEV_FL_HAS_EVENTS;

	v4l2_ctrl_handler_init(&mt9m111->hdl, 7);
	v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	mt9m111->gain = v4l2_ctrl_new_std(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_GAIN, 0, 63 * 2 * 2, 1, 32);
	v4l2_ctrl_new_std_menu(&mt9m111->hdl,
			&mt9m111_ctrl_ops, V4L2_CID_EXPOSURE_AUTO, 1, 0,
			V4L2_EXPOSURE_AUTO);
	v4l2_ctrl_new_std_menu_items(&mt9m111->hdl,
			&mt9m111_ctrl_ops, V4L2_CID_TEST_PATTERN,
			ARRAY_SIZE(mt9m111_test_pattern_menu) - 1, 0, 0,
			mt9m111_test_pattern_menu);
	v4l2_ctrl_new_std_menu(&mt9m111->hdl, &mt9m111_ctrl_ops,
			V4L2_CID_COLORFX, V4L2_COLORFX_SOLARIZATION,
			~(BIT(V4L2_COLORFX_NONE) |
				BIT(V4L2_COLORFX_BW) |
				BIT(V4L2_COLORFX_SEPIA) |
				BIT(V4L2_COLORFX_NEGATIVE) |
				BIT(V4L2_COLORFX_SOLARIZATION)),
			V4L2_COLORFX_NONE);
	mt9m111->subdev.ctrl_handler = &mt9m111->hdl;
	if (mt9m111->hdl.error) {
		ret = mt9m111->hdl.error;
		goto out_clkput;
	}

#ifdef CONFIG_MEDIA_CONTROLLER
	mt9m111->pad.flags = MEDIA_PAD_FL_SOURCE;
	mt9m111->subdev.entity.function = MEDIA_ENT_F_CAM_SENSOR;
	ret = media_entity_pads_init(&mt9m111->subdev.entity, 1, &mt9m111->pad);
	if (ret < 0)
		goto out_hdlfree;
#endif

	mt9m111->current_mode = &mt9m111_mode_data[MT9M111_MODE_SXGA_15FPS];
	mt9m111->frame_interval.numerator = 1;
	mt9m111->frame_interval.denominator = mt9m111->current_mode->max_fps;

	/* Second stage probe - when a capture adapter is there */
	mt9m111->rect.left	= MT9M111_MIN_DARK_COLS;
	mt9m111->rect.top	= MT9M111_MIN_DARK_ROWS;
	mt9m111->rect.width	= MT9M111_MAX_WIDTH;
	mt9m111->rect.height	= MT9M111_MAX_HEIGHT;
	mt9m111->width		= mt9m111->rect.width;
	mt9m111->height		= mt9m111->rect.height;
	mt9m111->fmt		= &mt9m111_colour_fmts[0];
	mt9m111->lastpage	= -1;
	mutex_init(&mt9m111->power_lock);

	ret = mt9m111_video_probe(client);
	if (ret < 0)
		goto out_entityclean;

	mt9m111->subdev.dev = &client->dev;
	ret = v4l2_async_register_subdev(&mt9m111->subdev);
	if (ret < 0)
		goto out_entityclean;

	return 0;

out_entityclean:
#ifdef CONFIG_MEDIA_CONTROLLER
	media_entity_cleanup(&mt9m111->subdev.entity);
out_hdlfree:
#endif
	v4l2_ctrl_handler_free(&mt9m111->hdl);
out_clkput:
	v4l2_clk_put(mt9m111->clk);

	return ret;
}