#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_subdev_desc {int dummy; } ;
struct TYPE_9__ {int error; } ;
struct TYPE_7__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_8__ {TYPE_3__* ctrl_handler; } ;
struct mt9t031 {int xskip; int yskip; TYPE_3__ hdl; int /*<<< orphan*/  clk; TYPE_1__ rect; scalar_t__ y_skip_top; int /*<<< orphan*/  autoexposure; TYPE_2__ subdev; int /*<<< orphan*/  exposure; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT9T031_COLUMN_SKIP ; 
 int /*<<< orphan*/  MT9T031_MAX_HEIGHT ; 
 int /*<<< orphan*/  MT9T031_MAX_WIDTH ; 
 int /*<<< orphan*/  MT9T031_ROW_SKIP ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct mt9t031* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t031_ctrl_ops ; 
 int /*<<< orphan*/  mt9t031_subdev_ops ; 
 int mt9t031_video_probe (struct i2c_client*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std_menu (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_2__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t031_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct mt9t031 *mt9t031;
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct i2c_adapter *adapter = client->adapter;
	int ret;

	if (!ssdd) {
		dev_err(&client->dev, "MT9T031 driver needs platform data\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA)) {
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_WORD\n");
		return -EIO;
	}

	mt9t031 = devm_kzalloc(&client->dev, sizeof(struct mt9t031), GFP_KERNEL);
	if (!mt9t031)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&mt9t031->subdev, client, &mt9t031_subdev_ops);
	v4l2_ctrl_handler_init(&mt9t031->hdl, 5);
	v4l2_ctrl_new_std(&mt9t031->hdl, &mt9t031_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9t031->hdl, &mt9t031_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&mt9t031->hdl, &mt9t031_ctrl_ops,
			V4L2_CID_GAIN, 0, 127, 1, 64);

	/*
	 * Simulated autoexposure. If enabled, we calculate shutter width
	 * ourselves in the driver based on vertical blanking and frame width
	 */
	mt9t031->autoexposure = v4l2_ctrl_new_std_menu(&mt9t031->hdl,
			&mt9t031_ctrl_ops, V4L2_CID_EXPOSURE_AUTO, 1, 0,
			V4L2_EXPOSURE_AUTO);
	mt9t031->exposure = v4l2_ctrl_new_std(&mt9t031->hdl, &mt9t031_ctrl_ops,
			V4L2_CID_EXPOSURE, 1, 255, 1, 255);

	mt9t031->subdev.ctrl_handler = &mt9t031->hdl;
	if (mt9t031->hdl.error)
		return mt9t031->hdl.error;

	v4l2_ctrl_auto_cluster(2, &mt9t031->autoexposure,
				V4L2_EXPOSURE_MANUAL, true);

	mt9t031->y_skip_top	= 0;
	mt9t031->rect.left	= MT9T031_COLUMN_SKIP;
	mt9t031->rect.top	= MT9T031_ROW_SKIP;
	mt9t031->rect.width	= MT9T031_MAX_WIDTH;
	mt9t031->rect.height	= MT9T031_MAX_HEIGHT;

	mt9t031->xskip = 1;
	mt9t031->yskip = 1;

	mt9t031->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(mt9t031->clk)) {
		ret = PTR_ERR(mt9t031->clk);
		goto eclkget;
	}

	ret = mt9t031_video_probe(client);
	if (ret) {
		v4l2_clk_put(mt9t031->clk);
eclkget:
		v4l2_ctrl_handler_free(&mt9t031->hdl);
	}

	return ret;
}