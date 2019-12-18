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
struct of_device_id {struct is31fl32xx_chipdef* data; } ;
struct is31fl32xx_priv {struct is31fl32xx_chipdef const* cdef; struct i2c_client* client; } ;
struct is31fl32xx_chipdef {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct is31fl32xx_priv* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct is31fl32xx_priv*) ; 
 int is31fl32xx_init_regs (struct is31fl32xx_priv*) ; 
 int is31fl32xx_parse_dt (struct device*,struct is31fl32xx_priv*) ; 
 int /*<<< orphan*/  leds ; 
 int of_get_child_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_is31fl32xx_match ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  struct_size (struct is31fl32xx_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int is31fl32xx_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	const struct is31fl32xx_chipdef *cdef;
	const struct of_device_id *of_dev_id;
	struct device *dev = &client->dev;
	struct is31fl32xx_priv *priv;
	int count;
	int ret = 0;

	of_dev_id = of_match_device(of_is31fl32xx_match, dev);
	if (!of_dev_id)
		return -EINVAL;

	cdef = of_dev_id->data;

	count = of_get_child_count(dev->of_node);
	if (!count)
		return -EINVAL;

	priv = devm_kzalloc(dev, struct_size(priv, leds, count),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->client = client;
	priv->cdef = cdef;
	i2c_set_clientdata(client, priv);

	ret = is31fl32xx_init_regs(priv);
	if (ret)
		return ret;

	ret = is31fl32xx_parse_dt(dev, priv);
	if (ret)
		return ret;

	return 0;
}