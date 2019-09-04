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
struct v4l2_rect {int width; int height; int left; int top; } ;
struct soc_camera_subdev_desc {scalar_t__ drv_priv; } ;
struct mt9t112_priv {int /*<<< orphan*/  clk; int /*<<< orphan*/  subdev; scalar_t__ info; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int MAX_HEIGHT ; 
 int MAX_WIDTH ; 
 int /*<<< orphan*/  MEDIA_BUS_FMT_UYVY8_2X8 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int VGA_HEIGHT ; 
 int VGA_WIDTH ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct mt9t112_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int mt9t112_camera_probe (struct i2c_client*) ; 
 int /*<<< orphan*/  mt9t112_set_params (struct mt9t112_priv*,struct v4l2_rect*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt9t112_subdev_ops ; 
 struct soc_camera_subdev_desc* soc_camera_i2c_to_desc (struct i2c_client*) ; 
 int /*<<< orphan*/  v4l2_clk_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  v4l2_clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_i2c_subdev_init (int /*<<< orphan*/ *,struct i2c_client*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mt9t112_probe(struct i2c_client *client,
			 const struct i2c_device_id *did)
{
	struct mt9t112_priv *priv;
	struct soc_camera_subdev_desc *ssdd = soc_camera_i2c_to_desc(client);
	struct v4l2_rect rect = {
		.width = VGA_WIDTH,
		.height = VGA_HEIGHT,
		.left = (MAX_WIDTH - VGA_WIDTH) / 2,
		.top = (MAX_HEIGHT - VGA_HEIGHT) / 2,
	};
	int ret;

	if (!ssdd || !ssdd->drv_priv) {
		dev_err(&client->dev, "mt9t112: missing platform data!\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(&client->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->info = ssdd->drv_priv;

	v4l2_i2c_subdev_init(&priv->subdev, client, &mt9t112_subdev_ops);

	priv->clk = v4l2_clk_get(&client->dev, "mclk");
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	ret = mt9t112_camera_probe(client);

	/* Cannot fail: using the default supported pixel code */
	if (!ret)
		mt9t112_set_params(priv, &rect, MEDIA_BUS_FMT_UYVY8_2X8);
	else
		v4l2_clk_put(priv->clk);

	return ret;
}