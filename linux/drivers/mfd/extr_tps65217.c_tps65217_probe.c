#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tps65217 {TYPE_2__* dev; int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  regmap; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  irq; TYPE_2__ dev; } ;
struct TYPE_9__ {scalar_t__ num_resources; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 unsigned int TPS65217_CHIPID_CHIP_MASK ; 
 unsigned int TPS65217_CHIPID_REV_MASK ; 
 int /*<<< orphan*/  TPS65217_PROTECT_NONE ; 
 int /*<<< orphan*/  TPS65217_REG_CHIPID ; 
 int /*<<< orphan*/  TPS65217_REG_STATUS ; 
 int /*<<< orphan*/  TPS65217_STATUS_OFF ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_2__*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct tps65217* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (TYPE_2__*,int,TYPE_1__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct tps65217*) ; 
 int of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tps65217_irq_init (struct tps65217*,int /*<<< orphan*/ ) ; 
 int tps65217_reg_read (struct tps65217*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  tps65217_regmap_config ; 
 int tps65217_set_bits (struct tps65217*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* tps65217s ; 

__attribute__((used)) static int tps65217_probe(struct i2c_client *client)
{
	struct tps65217 *tps;
	unsigned int version;
	bool status_off = false;
	int ret;

	status_off = of_property_read_bool(client->dev.of_node,
					   "ti,pmic-shutdown-controller");

	tps = devm_kzalloc(&client->dev, sizeof(*tps), GFP_KERNEL);
	if (!tps)
		return -ENOMEM;

	i2c_set_clientdata(client, tps);
	tps->dev = &client->dev;

	tps->regmap = devm_regmap_init_i2c(client, &tps65217_regmap_config);
	if (IS_ERR(tps->regmap)) {
		ret = PTR_ERR(tps->regmap);
		dev_err(tps->dev, "Failed to allocate register map: %d\n",
			ret);
		return ret;
	}

	if (client->irq) {
		tps65217_irq_init(tps, client->irq);
	} else {
		int i;

		/* Don't tell children about IRQ resources which won't fire */
		for (i = 0; i < ARRAY_SIZE(tps65217s); i++)
			tps65217s[i].num_resources = 0;
	}

	ret = devm_mfd_add_devices(tps->dev, -1, tps65217s,
				   ARRAY_SIZE(tps65217s), NULL, 0,
				   tps->irq_domain);
	if (ret < 0) {
		dev_err(tps->dev, "mfd_add_devices failed: %d\n", ret);
		return ret;
	}

	ret = tps65217_reg_read(tps, TPS65217_REG_CHIPID, &version);
	if (ret < 0) {
		dev_err(tps->dev, "Failed to read revision register: %d\n",
			ret);
		return ret;
	}

	/* Set the PMIC to shutdown on PWR_EN toggle */
	if (status_off) {
		ret = tps65217_set_bits(tps, TPS65217_REG_STATUS,
				TPS65217_STATUS_OFF, TPS65217_STATUS_OFF,
				TPS65217_PROTECT_NONE);
		if (ret)
			dev_warn(tps->dev, "unable to set the status OFF\n");
	}

	dev_info(tps->dev, "TPS65217 ID %#x version 1.%d\n",
			(version & TPS65217_CHIPID_CHIP_MASK) >> 4,
			version & TPS65217_CHIPID_REV_MASK);

	return 0;
}