#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct soc_camera_subdev_desc {struct rj54n1_pdata* drv_priv; } ;
struct rj54n1_pdata {int mclk_freq; } ;
struct TYPE_12__ {int error; } ;
struct TYPE_10__ {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_14__ {int ratio_tg; int ratio_t; } ;
struct TYPE_11__ {TYPE_3__* ctrl_handler; } ;
struct rj54n1 {int resize; int tgclk_mhz; TYPE_3__ hdl; int /*<<< orphan*/  clk; int /*<<< orphan*/ * fmt; void* height; void* width; TYPE_1__ rect; TYPE_9__ clk_div; TYPE_2__ subdev; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  parent; } ;
struct i2c_client {TYPE_6__ dev; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PLL_L ; 
 int PLL_N ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RJ54N1_COLUMN_SKIP ; 
 void* RJ54N1_MAX_HEIGHT ; 
 void* RJ54N1_MAX_WIDTH ; 
 int /*<<< orphan*/  RJ54N1_ROW_SKIP ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 TYPE_9__ clk_div ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct rj54n1* devm_kzalloc (TYPE_6__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rj54n1_colour_fmts ; 
 int /*<<< orphan*/  rj54n1_ctrl_ops ; 
 int /*<<< orphan*/  rj54n1_subdev_ops ; 
 int rj54n1_video_probe (struct i2c_client*,struct rj54n1_pdata*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_clk_get (TYPE_6__*,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_2__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rj54n1_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct rj54n1 *rj54n1;
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct i2c_adapter *adapter = to_i2c_adapter(client->dev.parent);
	struct rj54n1_pdata *rj54n1_priv;
	int ret;

	if (!ssdd || !ssdd->drv_priv) {
		dev_err(&client->dev, "RJ54N1CB0C: missing platform data!\n");
		return -EINVAL;
	}

	rj54n1_priv = ssdd->drv_priv;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_BYTE\n");
		return -EIO;
	}

	rj54n1 = devm_kzalloc(&client->dev, sizeof(struct rj54n1), GFP_KERNEL);
	if (!rj54n1)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&rj54n1->subdev, client, &rj54n1_subdev_ops);
	v4l2_ctrl_handler_init(&rj54n1->hdl, 4);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_VFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_HFLIP, 0, 1, 1, 0);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_GAIN, 0, 127, 1, 66);
	v4l2_ctrl_new_std(&rj54n1->hdl, &rj54n1_ctrl_ops,
			V4L2_CID_AUTO_WHITE_BALANCE, 0, 1, 1, 1);
	rj54n1->subdev.ctrl_handler = &rj54n1->hdl;
	if (rj54n1->hdl.error)
		return rj54n1->hdl.error;

	rj54n1->clk_div		= clk_div;
	rj54n1->rect.left	= RJ54N1_COLUMN_SKIP;
	rj54n1->rect.top	= RJ54N1_ROW_SKIP;
	rj54n1->rect.width	= RJ54N1_MAX_WIDTH;
	rj54n1->rect.height	= RJ54N1_MAX_HEIGHT;
	rj54n1->width		= RJ54N1_MAX_WIDTH;
	rj54n1->height		= RJ54N1_MAX_HEIGHT;
	rj54n1->fmt		= &rj54n1_colour_fmts[0];
	rj54n1->resize		= 1024;
	rj54n1->tgclk_mhz	= (rj54n1_priv->mclk_freq / PLL_L * PLL_N) /
		(clk_div.ratio_tg + 1) / (clk_div.ratio_t + 1);

	rj54n1->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(rj54n1->clk)) {
		ret = PTR_ERR(rj54n1->clk);
		goto eclkget;
	}

	ret = rj54n1_video_probe(client, rj54n1_priv);
	if (ret < 0) {
		v4l2_clk_put(rj54n1->clk);
eclkget:
		v4l2_ctrl_handler_free(&rj54n1->hdl);
	}

	return ret;
}