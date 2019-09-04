#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
struct rj54n1_pdata {int mclk_freq; } ;
struct TYPE_16__ {int error; } ;
struct TYPE_15__ {TYPE_3__* ctrl_handler; } ;
struct TYPE_14__ {void* height; void* width; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_13__ {int ratio_tg; int ratio_t; } ;
struct rj54n1 {int resize; int tgclk_mhz; TYPE_3__ hdl; void* clk; void* pwup_gpio; void* enable_gpio; TYPE_2__ subdev; int /*<<< orphan*/ * fmt; void* height; void* width; TYPE_1__ rect; TYPE_12__ clk_div; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_17__ {struct rj54n1_pdata* platform_data; } ;
struct i2c_client {TYPE_7__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (void*) ; 
 int PLL_L ; 
 int PLL_N ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  RJ54N1_COLUMN_SKIP ; 
 void* RJ54N1_MAX_HEIGHT ; 
 void* RJ54N1_MAX_WIDTH ; 
 int /*<<< orphan*/  RJ54N1_ROW_SKIP ; 
 int /*<<< orphan*/  V4L2_CID_AUTO_WHITE_BALANCE ; 
 int /*<<< orphan*/  V4L2_CID_GAIN ; 
 int /*<<< orphan*/  V4L2_CID_HFLIP ; 
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 TYPE_12__ clk_div ; 
 void* clk_get (TYPE_7__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_put (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_7__*,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct rj54n1* devm_kzalloc (TYPE_7__*,int,int /*<<< orphan*/ ) ; 
 void* gpiod_get_optional (TYPE_7__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (void*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rj54n1_colour_fmts ; 
 int /*<<< orphan*/  rj54n1_ctrl_ops ; 
 int /*<<< orphan*/  rj54n1_subdev_ops ; 
 int rj54n1_video_probe (struct i2c_client*,struct rj54n1_pdata*) ; 
 int v4l2_async_register_subdev (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_init (TYPE_3__*,int) ; 
 int /*<<< orphan*/  v4l2_ctrl_new_std (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (TYPE_2__*,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rj54n1_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct rj54n1 *rj54n1;
	struct i2c_adapter *adapter = client->adapter;
	struct rj54n1_pdata *rj54n1_priv;
	int ret;

	if (!client->dev.platform_data) {
		dev_err(&client->dev, "RJ54N1CB0C: missing platform data!\n");
		return -EINVAL;
	}

	rj54n1_priv = client->dev.platform_data;

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

	rj54n1->clk = clk_get(&client->dev, NULL);
	if (IS_ERR(rj54n1->clk)) {
		ret = PTR_ERR(rj54n1->clk);
		goto err_free_ctrl;
	}

	rj54n1->pwup_gpio = gpiod_get_optional(&client->dev, "powerup",
					       GPIOD_OUT_LOW);
	if (IS_ERR(rj54n1->pwup_gpio)) {
		dev_info(&client->dev, "Unable to get GPIO \"powerup\": %ld\n",
			 PTR_ERR(rj54n1->pwup_gpio));
		ret = PTR_ERR(rj54n1->pwup_gpio);
		goto err_clk_put;
	}

	rj54n1->enable_gpio = gpiod_get_optional(&client->dev, "enable",
						 GPIOD_OUT_LOW);
	if (IS_ERR(rj54n1->enable_gpio)) {
		dev_info(&client->dev, "Unable to get GPIO \"enable\": %ld\n",
			 PTR_ERR(rj54n1->enable_gpio));
		ret = PTR_ERR(rj54n1->enable_gpio);
		goto err_gpio_put;
	}

	ret = rj54n1_video_probe(client, rj54n1_priv);
	if (ret < 0)
		goto err_gpio_put;

	ret = v4l2_async_register_subdev(&rj54n1->subdev);
	if (ret)
		goto err_gpio_put;

	return 0;

err_gpio_put:
	if (rj54n1->enable_gpio)
		gpiod_put(rj54n1->enable_gpio);

	if (rj54n1->pwup_gpio)
		gpiod_put(rj54n1->pwup_gpio);

err_clk_put:
	clk_put(rj54n1->clk);

err_free_ctrl:
	v4l2_ctrl_handler_free(&rj54n1->hdl);

	return ret;
}