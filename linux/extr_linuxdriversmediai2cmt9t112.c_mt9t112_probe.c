#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mt9t112_priv {int init_done; int /*<<< orphan*/  subdev; int /*<<< orphan*/ * standby_gpio; int /*<<< orphan*/ * clk; scalar_t__ info; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_5__ {scalar_t__ platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * devm_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * devm_gpiod_get_optional (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 struct mt9t112_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int mt9t112_camera_probe (struct i2c_client*) ; 
 int /*<<< orphan*/  mt9t112_subdev_ops ; 
 int v4l2_async_register_subdev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t112_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct mt9t112_priv *priv;
	int ret;

	if (!client->dev.platform_data) {
		dev_err(&client->dev, "mt9t112: missing platform data!\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info = client->dev.platform_data;
	priv->init_done = false;

	v4l2_i2c_subdev_init(&priv->subdev, client, &mt9t112_subdev_ops);

	priv->clk = devm_clk_get(&client->dev, "extclk");
	if (PTR_ERR(priv->clk) == -ENOENT) {
		priv->clk = NULL;
	} else if (IS_ERR(priv->clk)) {
		dev_err(&client->dev, "Unable to get clock \"extclk\"\n");
		return PTR_ERR(priv->clk);
	}

	priv->standby_gpio = devm_gpiod_get_optional(&client->dev, "standby",
						     GPIOD_OUT_HIGH);
	if (IS_ERR(priv->standby_gpio)) {
		dev_err(&client->dev, "Unable to get gpio \"standby\"\n");
		return PTR_ERR(priv->standby_gpio);
	}

	ret = mt9t112_camera_probe(client);
	if (ret)
		return ret;

	return v4l2_async_register_subdev(&priv->subdev);
}