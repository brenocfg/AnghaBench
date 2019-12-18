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
struct ov2640_priv {void* pwdn_gpio; void* resetb_gpio; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOSYS ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int PTR_ERR_OR_ZERO (void*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_gpiod_get_optional (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ov2640_probe_dt(struct i2c_client *client,
		struct ov2640_priv *priv)
{
	int ret;

	/* Request the reset GPIO deasserted */
	priv->resetb_gpio = devm_gpiod_get_optional(&client->dev, "resetb",
			GPIOD_OUT_LOW);

	if (!priv->resetb_gpio)
		dev_dbg(&client->dev, "resetb gpio is not assigned!\n");

	ret = PTR_ERR_OR_ZERO(priv->resetb_gpio);
	if (ret && ret != -ENOSYS) {
		dev_dbg(&client->dev,
			"Error %d while getting resetb gpio\n", ret);
		return ret;
	}

	/* Request the power down GPIO asserted */
	priv->pwdn_gpio = devm_gpiod_get_optional(&client->dev, "pwdn",
			GPIOD_OUT_HIGH);

	if (!priv->pwdn_gpio)
		dev_dbg(&client->dev, "pwdn gpio is not assigned!\n");

	ret = PTR_ERR_OR_ZERO(priv->pwdn_gpio);
	if (ret && ret != -ENOSYS) {
		dev_dbg(&client->dev,
			"Error %d while getting pwdn gpio\n", ret);
		return ret;
	}

	return 0;
}