#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tw9910_video_info {int dummy; } ;
struct tw9910_priv {int /*<<< orphan*/ * clk; int /*<<< orphan*/ * pdn_gpio; int /*<<< orphan*/  subdev; struct tw9910_video_info* info; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {struct tw9910_video_info* platform_data; } ;
struct i2c_client {TYPE_1__ dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 struct tw9910_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw9910_subdev_ops ; 
 int tw9910_video_probe (struct i2c_client*) ; 
 int v4l2_async_register_subdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tw9910_probe(struct i2c_client *client,
			const struct i2c_device_id *did)

{
	struct tw9910_priv		*priv;
	struct tw9910_video_info	*info;
	struct i2c_adapter		*adapter = client->adapter;
	int ret;

	if (!client->dev.platform_data) {
		dev_err(&client->dev, "TW9910: missing platform data!\n");
		return -EINVAL;
	}

	info = client->dev.platform_data;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev,
			"I2C-Adapter doesn't support I2C_FUNC_SMBUS_BYTE_DATA\n");
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info = info;

	v4l2_i2c_subdev_init(&priv->subdev, client, &tw9910_subdev_ops);

	priv->clk = clk_get(&client->dev, "xti");
	if (PTR_ERR(priv->clk) == -ENOENT) {
		priv->clk = NULL;
	} else if (IS_ERR(priv->clk)) {
		dev_err(&client->dev, "Unable to get xti clock\n");
		return PTR_ERR(priv->clk);
	}

	priv->pdn_gpio = gpiod_get_optional(&client->dev, "pdn",
					    GPIOD_OUT_HIGH);
	if (IS_ERR(priv->pdn_gpio)) {
		dev_info(&client->dev, "Unable to get GPIO \"pdn\"");
		ret = PTR_ERR(priv->pdn_gpio);
		goto error_clk_put;
	}

	ret = tw9910_video_probe(client);
	if (ret < 0)
		goto error_gpio_put;

	ret = v4l2_async_register_subdev(&priv->subdev);
	if (ret)
		goto error_gpio_put;

	return ret;

error_gpio_put:
	if (priv->pdn_gpio)
		gpiod_put(priv->pdn_gpio);
error_clk_put:
	clk_put(priv->clk);

	return ret;
}