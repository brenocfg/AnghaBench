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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct cxd2820r_priv {int /*<<< orphan*/ * regmap; int /*<<< orphan*/ * client; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 struct cxd2820r_priv* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cxd2820r_priv*) ; 
 int /*<<< orphan*/  regmap_exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxd2820r_remove(struct i2c_client *client)
{
	struct cxd2820r_priv *priv = i2c_get_clientdata(client);

	dev_dbg(&client->dev, "\n");

#ifdef CONFIG_GPIOLIB
	if (priv->gpio_chip.label)
		gpiochip_remove(&priv->gpio_chip);
#endif
	regmap_exit(priv->regmap[1]);
	i2c_unregister_device(priv->client[1]);

	regmap_exit(priv->regmap[0]);

	kfree(priv);

	return 0;
}