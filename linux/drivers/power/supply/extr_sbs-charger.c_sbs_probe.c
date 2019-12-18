#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sbs_info {int last_state; int /*<<< orphan*/  work; int /*<<< orphan*/  power_supply; int /*<<< orphan*/  regmap; struct i2c_client* client; } ;
struct power_supply_config {struct sbs_info* drv_data; int /*<<< orphan*/  of_node; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; TYPE_1__ dev; scalar_t__ irq; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBS_CHARGER_POLL_TIME ; 
 int /*<<< orphan*/  SBS_CHARGER_REG_STATUS ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 struct sbs_info* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_power_supply_register (TYPE_1__*,int /*<<< orphan*/ *,struct power_supply_config*) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sbs_info*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct sbs_info*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sbs_delayed_work ; 
 int /*<<< orphan*/  sbs_desc ; 
 int /*<<< orphan*/  sbs_irq_thread ; 
 int /*<<< orphan*/  sbs_regmap ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbs_probe(struct i2c_client *client,
		     const struct i2c_device_id *id)
{
	struct power_supply_config psy_cfg = {};
	struct sbs_info *chip;
	int ret, val;

	chip = devm_kzalloc(&client->dev, sizeof(struct sbs_info), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->client = client;
	psy_cfg.of_node = client->dev.of_node;
	psy_cfg.drv_data = chip;

	i2c_set_clientdata(client, chip);

	chip->regmap = devm_regmap_init_i2c(client, &sbs_regmap);
	if (IS_ERR(chip->regmap))
		return PTR_ERR(chip->regmap);

	/*
	 * Before we register, we need to make sure we can actually talk
	 * to the battery.
	 */
	ret = regmap_read(chip->regmap, SBS_CHARGER_REG_STATUS, &val);
	if (ret) {
		dev_err(&client->dev, "Failed to get device status\n");
		return ret;
	}
	chip->last_state = val;

	chip->power_supply = devm_power_supply_register(&client->dev, &sbs_desc,
							&psy_cfg);
	if (IS_ERR(chip->power_supply)) {
		dev_err(&client->dev, "Failed to register power supply\n");
		return PTR_ERR(chip->power_supply);
	}

	/*
	 * The sbs-charger spec doesn't impose the use of an interrupt. So in
	 * the case it wasn't provided we use polling in order get the charger's
	 * status.
	 */
	if (client->irq) {
		ret = devm_request_threaded_irq(&client->dev, client->irq,
					NULL, sbs_irq_thread,
					IRQF_TRIGGER_FALLING | IRQF_ONESHOT,
					dev_name(&client->dev), chip);
		if (ret) {
			dev_err(&client->dev, "Failed to request irq, %d\n", ret);
			return ret;
		}
	} else {
		INIT_DELAYED_WORK(&chip->work, sbs_delayed_work);
		schedule_delayed_work(&chip->work,
				      msecs_to_jiffies(SBS_CHARGER_POLL_TIME));
	}

	dev_info(&client->dev,
		 "%s: smart charger device registered\n", client->name);

	return 0;
}