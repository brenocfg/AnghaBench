#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct power_supply_desc {int dummy; } ;
struct power_supply_config {int /*<<< orphan*/  of_node; struct max17042_chip* drv_data; } ;
struct max17042_chip {int init_complete; int /*<<< orphan*/  work; TYPE_4__* regmap; TYPE_4__* battery; TYPE_7__* pdata; int /*<<< orphan*/  chip_type; struct i2c_client* client; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; } ;
struct device {int /*<<< orphan*/  of_node; TYPE_1__* driver; } ;
struct i2c_client {struct device dev; scalar_t__ irq; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct acpi_device_id {int /*<<< orphan*/  driver_data; } ;
struct TYPE_16__ {scalar_t__ r_sns; int num_init_data; int /*<<< orphan*/  enable_current_sense; TYPE_2__* init_data; } ;
struct TYPE_15__ {TYPE_3__* desc; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {int data; int /*<<< orphan*/  addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_ALRT_BIT_ENBL ; 
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int IRQF_ONESHOT ; 
 unsigned int IRQF_PROBE_SHARED ; 
 unsigned int IRQF_SHARED ; 
 unsigned int IRQF_TRIGGER_FALLING ; 
 scalar_t__ IS_ERR (TYPE_4__*) ; 
 int /*<<< orphan*/  MAX17042_CGAIN ; 
 int /*<<< orphan*/  MAX17042_CONFIG ; 
 scalar_t__ MAX17042_DEFAULT_SNS_RESISTOR ; 
 int /*<<< orphan*/  MAX17042_LearnCFG ; 
 int /*<<< orphan*/  MAX17042_MiscCFG ; 
 int /*<<< orphan*/  MAX17042_SALRT_Th ; 
 int /*<<< orphan*/  MAX17042_STATUS ; 
 int PTR_ERR (TYPE_4__*) ; 
 int STATUS_POR_BIT ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_add_action (struct device*,int /*<<< orphan*/ ,struct max17042_chip*) ; 
 struct max17042_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* devm_power_supply_register (struct device*,struct power_supply_desc const*,struct power_supply_config*) ; 
 TYPE_4__* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,struct max17042_chip*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct max17042_chip*) ; 
 TYPE_7__* max17042_get_pdata (struct max17042_chip*) ; 
 int /*<<< orphan*/  max17042_init_worker ; 
 struct power_supply_desc max17042_no_current_sense_psy_desc ; 
 struct power_supply_desc max17042_psy_desc ; 
 int /*<<< orphan*/  max17042_regmap_config ; 
 int /*<<< orphan*/  max17042_set_soc_threshold (struct max17042_chip*,int) ; 
 int /*<<< orphan*/  max17042_stop_work ; 
 int /*<<< orphan*/  max17042_thread_handler ; 
 int /*<<< orphan*/  regmap_read (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int max17042_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	const struct power_supply_desc *max17042_desc = &max17042_psy_desc;
	struct power_supply_config psy_cfg = {};
	const struct acpi_device_id *acpi_id = NULL;
	struct device *dev = &client->dev;
	struct max17042_chip *chip;
	int ret;
	int i;
	u32 val;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_WORD_DATA))
		return -EIO;

	chip = devm_kzalloc(&client->dev, sizeof(*chip), GFP_KERNEL);
	if (!chip)
		return -ENOMEM;

	chip->client = client;
	if (id) {
		chip->chip_type = id->driver_data;
	} else {
		acpi_id = acpi_match_device(dev->driver->acpi_match_table, dev);
		if (!acpi_id)
			return -ENODEV;

		chip->chip_type = acpi_id->driver_data;
	}
	chip->regmap = devm_regmap_init_i2c(client, &max17042_regmap_config);
	if (IS_ERR(chip->regmap)) {
		dev_err(&client->dev, "Failed to initialize regmap\n");
		return -EINVAL;
	}

	chip->pdata = max17042_get_pdata(chip);
	if (!chip->pdata) {
		dev_err(&client->dev, "no platform data provided\n");
		return -EINVAL;
	}

	i2c_set_clientdata(client, chip);
	psy_cfg.drv_data = chip;
	psy_cfg.of_node = dev->of_node;

	/* When current is not measured,
	 * CURRENT_NOW and CURRENT_AVG properties should be invisible. */
	if (!chip->pdata->enable_current_sense)
		max17042_desc = &max17042_no_current_sense_psy_desc;

	if (chip->pdata->r_sns == 0)
		chip->pdata->r_sns = MAX17042_DEFAULT_SNS_RESISTOR;

	if (chip->pdata->init_data)
		for (i = 0; i < chip->pdata->num_init_data; i++)
			regmap_write(chip->regmap,
					chip->pdata->init_data[i].addr,
					chip->pdata->init_data[i].data);

	if (!chip->pdata->enable_current_sense) {
		regmap_write(chip->regmap, MAX17042_CGAIN, 0x0000);
		regmap_write(chip->regmap, MAX17042_MiscCFG, 0x0003);
		regmap_write(chip->regmap, MAX17042_LearnCFG, 0x0007);
	}

	chip->battery = devm_power_supply_register(&client->dev, max17042_desc,
						   &psy_cfg);
	if (IS_ERR(chip->battery)) {
		dev_err(&client->dev, "failed: power supply register\n");
		return PTR_ERR(chip->battery);
	}

	if (client->irq) {
		unsigned int flags = IRQF_TRIGGER_FALLING | IRQF_ONESHOT;

		/*
		 * On ACPI systems the IRQ may be handled by ACPI-event code,
		 * so we need to share (if the ACPI code is willing to share).
		 */
		if (acpi_id)
			flags |= IRQF_SHARED | IRQF_PROBE_SHARED;

		ret = devm_request_threaded_irq(&client->dev, client->irq,
						NULL,
						max17042_thread_handler, flags,
						chip->battery->desc->name,
						chip);
		if (!ret) {
			regmap_update_bits(chip->regmap, MAX17042_CONFIG,
					CONFIG_ALRT_BIT_ENBL,
					CONFIG_ALRT_BIT_ENBL);
			max17042_set_soc_threshold(chip, 1);
		} else {
			client->irq = 0;
			if (ret != -EBUSY)
				dev_err(&client->dev, "Failed to get IRQ\n");
		}
	}
	/* Not able to update the charge threshold when exceeded? -> disable */
	if (!client->irq)
		regmap_write(chip->regmap, MAX17042_SALRT_Th, 0xff00);

	regmap_read(chip->regmap, MAX17042_STATUS, &val);
	if (val & STATUS_POR_BIT) {
		INIT_WORK(&chip->work, max17042_init_worker);
		ret = devm_add_action(&client->dev, max17042_stop_work, chip);
		if (ret)
			return ret;
		schedule_work(&chip->work);
	} else {
		chip->init_complete = 1;
	}

	return 0;
}