#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ops; TYPE_2__* dev; int /*<<< orphan*/  regmap; } ;
struct lan9303_i2c {TYPE_1__ chip; struct i2c_client* device; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*) ; 
 struct lan9303_i2c* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct lan9303_i2c*) ; 
 int /*<<< orphan*/  lan9303_i2c_regmap_config ; 
 int /*<<< orphan*/  lan9303_indirect_phy_ops ; 
 int lan9303_probe (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lan9303_i2c_probe(struct i2c_client *client,
			     const struct i2c_device_id *id)
{
	struct lan9303_i2c *sw_dev;
	int ret;

	sw_dev = devm_kzalloc(&client->dev, sizeof(struct lan9303_i2c),
			      GFP_KERNEL);
	if (!sw_dev)
		return -ENOMEM;

	sw_dev->chip.regmap = devm_regmap_init_i2c(client,
						   &lan9303_i2c_regmap_config);
	if (IS_ERR(sw_dev->chip.regmap)) {
		ret = PTR_ERR(sw_dev->chip.regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	/* link forward and backward */
	sw_dev->device = client;
	i2c_set_clientdata(client, sw_dev);
	sw_dev->chip.dev = &client->dev;

	sw_dev->chip.ops = &lan9303_indirect_phy_ops;

	ret = lan9303_probe(&sw_dev->chip, client->dev.of_node);
	if (ret != 0)
		return ret;

	dev_info(&client->dev, "LAN9303 I2C driver loaded successfully\n");

	return 0;
}