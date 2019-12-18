#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int error; } ;
struct TYPE_9__ {int /*<<< orphan*/ * internal_ops; TYPE_3__* ctrl_handler; } ;
struct TYPE_8__ {int left; int top; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct ov6650 {int half_scale; TYPE_3__ hdl; TYPE_2__ subdev; int /*<<< orphan*/  colorspace; int /*<<< orphan*/  code; TYPE_1__ rect; void* autoexposure; void* autowb; void* autogain; void* exposure; void* red; void* blue; void* gain; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DEF_AECH ; 
 int DEF_BLUE ; 
 int DEF_GAIN ; 
 int DEF_HSTRT ; 
 int DEF_HUE ; 
 int DEF_RED ; 
 int DEF_VSTRT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HUE_MASK ; 
 int /*<<< orphan*/  H_CIF ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_YUYV8_2X8 ; 
 int /*<<< orphan*/  V4L2_CID_AUTOGAIN ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_BLUE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_BRIGHTNESS ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE ; 
 int /*<<< orphan*/  V4L2_CID_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_GAMMA ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_HUE ; 
 int /*<<< orphan*/  V4L2_CID_RED_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_SATURATION ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  V4L2_COLORSPACE_JPEG ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_AUTO ; 
 int /*<<< orphan*/  V4L2_EXPOSURE_MANUAL ; 
 int /*<<< orphan*/  W_CIF ; 
 struct ov6650* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ov6550_ctrl_ops ; 
 int /*<<< orphan*/  ov6650_internal_ops ; 
 int /*<<< orphan*/  ov6650_subdev_ops ; 
 int v4l2_async_register_subdev (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_auto_cluster (int,void**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 void* v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 void* v4l2_ctrl_new_std_menu (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_2__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov6650_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct ov6650 *priv;
	int ret;

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&priv->subdev, client, &ov6650_subdev_ops);
	v4l2_ctrl_handler_init(&priv->hdl, 13);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	priv->autogain = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_AUTOGAIN, 0, 1, 1, 1);
	priv->gain = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_GAIN, 0, 0x3f, 1, DEF_GAIN);
	priv->autowb = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	priv->blue = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_BLUE_BALANCE, 0, 0xff, 1, DEF_BLUE);
	priv->red = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_RED_BALANCE, 0, 0xff, 1, DEF_RED);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_SATURATION, 0, 0xf, 1, 0x8);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_HUE, 0, HUE_MASK, 1, DEF_HUE);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_BRIGHTNESS, 0, 0xff, 1, 0x80);
	priv->autoexposure = v4l2_ctrl_new_std_menu(&priv->hdl,
			&ov6550_ctrl_ops, V4L2_CID_EXPOSURE_AUTO,
			V4L2_EXPOSURE_MANUAL, 0, V4L2_EXPOSURE_AUTO);
	priv->exposure = v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_EXPOSURE, 0, 0xff, 1, DEF_AECH);
	v4l2_ctrl_new_std(&priv->hdl, &ov6550_ctrl_ops,
			V4L2_CID_GAMMA, 0, 0xff, 1, 0x12);

	priv->subdev.ctrl_handler = &priv->hdl;
	if (priv->hdl.error)
		return priv->hdl.error;

	v4l2_ctrl_auto_cluster(2, &priv->autogain, 0, true);
	v4l2_ctrl_auto_cluster(3, &priv->autowb, 0, true);
	v4l2_ctrl_auto_cluster(2, &priv->autoexposure,
				V4L2_EXPOSURE_MANUAL, true);

	priv->rect.left	  = DEF_HSTRT << 1;
	priv->rect.top	  = DEF_VSTRT << 1;
	priv->rect.width  = W_CIF;
	priv->rect.height = H_CIF;
	priv->half_scale  = false;
	priv->code	  = MEDIA_BUS_FMT_YUYV8_2X8;
	priv->colorspace  = V4L2_COLORSPACE_JPEG;

	priv->subdev.internal_ops = &ov6650_internal_ops;

	ret = v4l2_async_register_subdev(&priv->subdev);
	if (ret)
		v4l2_ctrl_handler_free(&priv->hdl);

	return ret;
}