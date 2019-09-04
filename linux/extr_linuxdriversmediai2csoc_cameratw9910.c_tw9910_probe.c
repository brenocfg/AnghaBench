#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tw9910_video_info {int dummy; } ;
struct tw9910_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  subdev; struct tw9910_video_info* info; } ;
struct soc_camera_subdev_desc {struct tw9910_video_info* drv_priv; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct tw9910_priv* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 struct i2c_adapter* to_i2c_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw9910_subdev_ops ; 
 int tw9910_video_probe (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tw9910_probe(struct i2c_client *client,
			const struct i2c_device_id *did)

{
	struct tw9910_priv		*priv;
	struct tw9910_video_info	*info;
	struct i2c_adapter		*adapter =
		to_i2c_adapter(client->dev.parent);
	struct soc_camera_subdev_desc	*ssdd = soc_camera_i2c_to_desc(client);
	int ret;

	if (!ssdd || !ssdd->drv_priv) {
		dev_err(&client->dev, "TW9910: missing platform data!\n");
		return -EINVAL;
	}

	info = ssdd->drv_priv;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(&client->dev,
			"I2C-Adapter doesn't support I2C_FUNC_SMBUS_BYTE_DATA\n");
		return -EIO;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info   = info;

	v4l2_i2c_subdev_init(&priv->subdev, client, &tw9910_subdev_ops);

	priv->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	ret = tw9910_video_probe(client);
	if (ret < 0)
		v4l2_clk_put(priv->clk);

	return ret;
}