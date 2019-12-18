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
struct ov772x_priv {scalar_t__ rstb_gpio; scalar_t__ clk; scalar_t__ pwdn_gpio; int /*<<< orphan*/  subdev; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_put (scalar_t__) ; 
 int /*<<< orphan*/  gpiod_set_value (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ov772x_power_on(struct ov772x_priv *priv)
{
	struct i2c_client *client = v4l2_get_subdevdata(&priv->subdev);
	int ret;

	if (priv->clk) {
		ret = clk_prepare_enable(priv->clk);
		if (ret)
			return ret;
	}

	if (priv->pwdn_gpio) {
		gpiod_set_value(priv->pwdn_gpio, 1);
		usleep_range(500, 1000);
	}

	/*
	 * FIXME: The reset signal is connected to a shared GPIO on some
	 * platforms (namely the SuperH Migo-R). Until a framework becomes
	 * available to handle this cleanly, request the GPIO temporarily
	 * to avoid conflicts.
	 */
	priv->rstb_gpio = gpiod_get_optional(&client->dev, "reset",
					     GPIOD_OUT_LOW);
	if (IS_ERR(priv->rstb_gpio)) {
		dev_info(&client->dev, "Unable to get GPIO \"reset\"");
		clk_disable_unprepare(priv->clk);
		return PTR_ERR(priv->rstb_gpio);
	}

	if (priv->rstb_gpio) {
		gpiod_set_value(priv->rstb_gpio, 1);
		usleep_range(500, 1000);
		gpiod_set_value(priv->rstb_gpio, 0);
		usleep_range(500, 1000);

		gpiod_put(priv->rstb_gpio);
	}

	return 0;
}