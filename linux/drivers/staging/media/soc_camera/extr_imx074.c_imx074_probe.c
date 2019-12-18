#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct soc_camera_subdev_desc {int dummy; } ;
struct imx074 {int /*<<< orphan*/  clk; int /*<<< orphan*/  subdev; int /*<<< orphan*/ * fmt; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct imx074* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * imx074_colour_fmts ; 
 int /*<<< orphan*/  imx074_subdev_ops ; 
 int imx074_video_probe (struct i2c_client*) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int soc_camera_power_init (int /*<<< orphan*/ *,struct soc_camera_subdev_desc*) ; 
 int v4l2_async_register_subdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int imx074_probe(struct i2c_client *client,
			const struct i2c_device_id *did)
{
	struct imx074 *priv;
	struct i2c_adapter *adapter = client->adapter;
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	int ret;

	if (!ssdd) {
		dev_err(&client->dev, "IMX074: missing platform data!\n");
		return -EINVAL;
	}

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_warn(&adapter->dev,
			 "I2C-Adapter doesn't support I2C_FUNC_SMBUS_BYTE\n");
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(struct imx074), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	v4l2_i2c_subdev_init(&priv->subdev, client, &imx074_subdev_ops);

	priv->fmt	= &imx074_colour_fmts[0];

	priv->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(priv->clk)) {
		dev_info(&client->dev, "Error %ld getting clock\n", PTR_ERR(priv->clk));
		return -EPROBE_DEFER;
	}

	ret = soc_camera_power_init(&client->dev, ssdd);
	if (ret < 0)
		goto epwrinit;

	ret = imx074_video_probe(client);
	if (ret < 0)
		goto eprobe;

	ret = v4l2_async_register_subdev(&priv->subdev);
	if (!ret)
		return 0;

epwrinit:
eprobe:
	v4l2_clk_put(priv->clk);
	return ret;
}