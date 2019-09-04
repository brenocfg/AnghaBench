#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_subdev_desc {int dummy; } ;
struct TYPE_12__ {int error; } ;
struct TYPE_10__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_11__ {TYPE_3__* ctrl_handler; } ;
struct mt9m001 {TYPE_3__ hdl; int /*<<< orphan*/  clk; TYPE_1__ rect; scalar_t__ y_skip_top; int /*<<< orphan*/  autoexposure; TYPE_2__ subdev; int /*<<< orphan*/  exposure; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  parent; } ;
struct i2c_client {TYPE_7__ dev; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT9M001_COLUMN_SKIP ; 
 int /*<<< orphan*/  MT9M001_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9M001_MAX_WIDTH ; 
 int /*<<< orphan*/  MT9M001_ROW_SKIP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct mt9m001* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9m001_ctrl_ops ; 
 int /*<<< orphan*/  mt9m001_subdev_ops ; 
 int mt9m001_video_probe (struct soc_camera_subdev_desc*,struct i2c_client*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_clk_get (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_2__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9m001_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct mt9m001 *mt9m001;
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	int ret;

	if (!ssdd) {
		dev_err(&client->dev, "MT9M001 driver needs platform data\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		return -EIO;
	}

	mt9m001 = devm_kzalloc(&client->dev, sizeof(struct mt9m001), GFP_KERNEL);
	if (!mt9m001)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&mt9m001->subdev, client, &mt9m001_subdev_ops);
	v4l2_ctrl_handler_init(&mt9m001->hdl, 4);
	v4l2_ctrl_new_std(&mt9m001->hdl, &mt9m001_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9m001->hdl, &mt9m001_ctrl_ops,
			V4L2_CID_GAIN, 0, 127, 1, 64);
	mt9m001->exposure = v4l2_ctrl_new_std(&mt9m001->hdl, &mt9m001_ctrl_ops,
			V4L2_CID_EXPOSURE, 1, 255, 1, 255);
	/*
	 * Simulated autoexposure. If enabled, we calculate shutter width
	 * ourselves in the driver based on vertical blanking and frame width
	 */
	mt9m001->autoexposure = v4l2_ctrl_new_std_menu(&mt9m001->hdl,
			&mt9m001_ctrl_ops, V4L2_CID_EXPOSURE_AUTO, 1, 0,
			V4L2_EXPOSURE_AUTO);
	mt9m001->subdev.ctrl_handler = &mt9m001->hdl;
	if (mt9m001->hdl.error)
		return mt9m001->hdl.error;

	v4l2_ctrl_auto_cluster(2, &mt9m001->autoexposure,
					V4L2_EXPOSURE_MANUAL, true);

	/* Second stage probe - when a capture adapter is there */
	mt9m001->y_skip_top	= 0;
	mt9m001->rect.left	= MT9M001_COLUMN_SKIP;
	mt9m001->rect.top	= MT9M001_ROW_SKIP;
	mt9m001->rect.width	= MT9M001_MAX_WIDTH;
	mt9m001->rect.height	= MT9M001_MAX_HEIGHT;

	mt9m001->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(mt9m001->clk)) {
		ret = PTR_ERR(mt9m001->clk);
		goto eclkget;
	}

	ret = mt9m001_video_probe(ssdd, client);
	if (ret) {
		v4l2_clk_put(mt9m001->clk);
eclkget:
		v4l2_ctrl_handler_free(&mt9m001->hdl);
	}

	return ret;
}