#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct of_device_id {struct i2c_device_id* data; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_3__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  irq; } ;
struct device_node {int dummy; } ;
struct da9052 {int /*<<< orphan*/  regmap; int /*<<< orphan*/  fix_io; int /*<<< orphan*/  chip_irq; TYPE_1__* dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int da9052_device_init (struct da9052*,int /*<<< orphan*/ ) ; 
 int da9052_i2c_disable_multiwrite (struct da9052*) ; 
 int /*<<< orphan*/  da9052_i2c_fix ; 
 int /*<<< orphan*/  da9052_regmap_config ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct da9052* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dialog_dt_ids ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct da9052*) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,struct device_node*) ; 

__attribute__((used)) static int da9052_i2c_probe(struct i2c_client *client,
				       const struct i2c_device_id *id)
{
	struct da9052 *da9052;
	int ret;

	da9052 = devm_kzalloc(&client->dev, sizeof(struct da9052), GFP_KERNEL);
	if (!da9052)
		return -ENOMEM;

	da9052->dev = &client->dev;
	da9052->chip_irq = client->irq;
	da9052->fix_io = da9052_i2c_fix;

	i2c_set_clientdata(client, da9052);

	da9052->regmap = devm_regmap_init_i2c(client, &da9052_regmap_config);
	if (IS_ERR(da9052->regmap)) {
		ret = PTR_ERR(da9052->regmap);
		dev_err(&client->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	ret = da9052_i2c_disable_multiwrite(da9052);
	if (ret < 0)
		return ret;

#ifdef CONFIG_OF
	if (!id) {
		struct device_node *np = client->dev.of_node;
		const struct of_device_id *deviceid;

		deviceid = of_match_node(dialog_dt_ids, np);
		id = deviceid->data;
	}
#endif

	if (!id) {
		ret = -ENODEV;
		dev_err(&client->dev, "id is null.\n");
		return ret;
	}

	return da9052_device_init(da9052, id->driver_data);
}