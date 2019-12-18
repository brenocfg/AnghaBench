#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct reg_field {int dummy; } ;
struct i2c_device_id {scalar_t__ driver_data; } ;
struct device {int /*<<< orphan*/  platform_data; TYPE_1__* driver; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; struct i2c_adapter* adapter; } ;
struct i2c_adapter {int dummy; } ;
struct bq24257_device {int chip; int iilimit_autoset_enable; struct device* dev; int /*<<< orphan*/  pg; int /*<<< orphan*/  iilimit_setup_work; int /*<<< orphan*/ * rmap_fields; int /*<<< orphan*/  rmap; int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct acpi_device_id {scalar_t__ driver_data; } ;
typedef  enum bq2425x_chip { ____Placeholder_bq2425x_chip } bq2425x_chip ;
struct TYPE_2__ {int /*<<< orphan*/  acpi_match_table; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (struct device*) ; 
 int ARRAY_SIZE (struct reg_field*) ; 
 scalar_t__ BQ24250 ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  F_RESET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I2C_FUNC_SMBUS_BYTE_DATA ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int bq24257_field_write (struct bq24257_device*,int /*<<< orphan*/ ,int) ; 
 int bq24257_fw_probe (struct bq24257_device*) ; 
 int bq24257_hw_init (struct bq24257_device*) ; 
 int /*<<< orphan*/  bq24257_iilimit_setup_work ; 
 int /*<<< orphan*/  bq24257_irq_handler_thread ; 
 int /*<<< orphan*/  bq24257_pg_gpio_probe (struct bq24257_device*) ; 
 int bq24257_power_supply_init (struct bq24257_device*) ; 
 struct reg_field* bq24257_reg_fields ; 
 int /*<<< orphan*/  bq24257_regmap_config ; 
 int /*<<< orphan*/ * bq2425x_chip_name ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 struct bq24257_device* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_field_alloc (struct device*,int /*<<< orphan*/ ,struct reg_field const) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct bq24257_device*) ; 
 int /*<<< orphan*/  i2c_check_functionality (struct i2c_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct bq24257_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bq24257_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct i2c_adapter *adapter = client->adapter;
	struct device *dev = &client->dev;
	const struct acpi_device_id *acpi_id;
	struct bq24257_device *bq;
	int ret;
	int i;

	if (!i2c_check_functionality(adapter, I2C_FUNC_SMBUS_BYTE_DATA)) {
		dev_err(dev, "No support for SMBUS_BYTE_DATA\n");
		return -ENODEV;
	}

	bq = devm_kzalloc(dev, sizeof(*bq), GFP_KERNEL);
	if (!bq)
		return -ENOMEM;

	bq->client = client;
	bq->dev = dev;

	if (ACPI_HANDLE(dev)) {
		acpi_id = acpi_match_device(dev->driver->acpi_match_table,
					    &client->dev);
		if (!acpi_id) {
			dev_err(dev, "Failed to match ACPI device\n");
			return -ENODEV;
		}
		bq->chip = (enum bq2425x_chip)acpi_id->driver_data;
	} else {
		bq->chip = (enum bq2425x_chip)id->driver_data;
	}

	mutex_init(&bq->lock);

	bq->rmap = devm_regmap_init_i2c(client, &bq24257_regmap_config);
	if (IS_ERR(bq->rmap)) {
		dev_err(dev, "failed to allocate register map\n");
		return PTR_ERR(bq->rmap);
	}

	for (i = 0; i < ARRAY_SIZE(bq24257_reg_fields); i++) {
		const struct reg_field *reg_fields = bq24257_reg_fields;

		bq->rmap_fields[i] = devm_regmap_field_alloc(dev, bq->rmap,
							     reg_fields[i]);
		if (IS_ERR(bq->rmap_fields[i])) {
			dev_err(dev, "cannot allocate regmap field\n");
			return PTR_ERR(bq->rmap_fields[i]);
		}
	}

	i2c_set_clientdata(client, bq);

	if (!dev->platform_data) {
		ret = bq24257_fw_probe(bq);
		if (ret < 0) {
			dev_err(dev, "Cannot read device properties.\n");
			return ret;
		}
	} else {
		return -ENODEV;
	}

	/*
	 * The BQ24250 doesn't support the D+/D- based charger type detection
	 * used for the automatic setting of the input current limit setting so
	 * explicitly disable that feature.
	 */
	if (bq->chip == BQ24250)
		bq->iilimit_autoset_enable = false;

	if (bq->iilimit_autoset_enable)
		INIT_DELAYED_WORK(&bq->iilimit_setup_work,
				  bq24257_iilimit_setup_work);

	/*
	 * The BQ24250 doesn't have a dedicated Power Good (PG) pin so let's
	 * not probe for it and instead use a SW-based approach to determine
	 * the PG state. We also use a SW-based approach for all other devices
	 * if the PG pin is either not defined or can't be probed.
	 */
	if (bq->chip != BQ24250)
		bq24257_pg_gpio_probe(bq);

	if (PTR_ERR(bq->pg) == -EPROBE_DEFER)
		return PTR_ERR(bq->pg);
	else if (!bq->pg)
		dev_info(bq->dev, "using SW-based power-good detection\n");

	/* reset all registers to defaults */
	ret = bq24257_field_write(bq, F_RESET, 1);
	if (ret < 0)
		return ret;

	/*
	 * Put the RESET bit back to 0, in cache. For some reason the HW always
	 * returns 1 on this bit, so this is the only way to avoid resetting the
	 * chip every time we update another field in this register.
	 */
	ret = bq24257_field_write(bq, F_RESET, 0);
	if (ret < 0)
		return ret;

	ret = bq24257_hw_init(bq);
	if (ret < 0) {
		dev_err(dev, "Cannot initialize the chip.\n");
		return ret;
	}

	ret = bq24257_power_supply_init(bq);
	if (ret < 0) {
		dev_err(dev, "Failed to register power supply\n");
		return ret;
	}

	ret = devm_request_threaded_irq(dev, client->irq, NULL,
					bq24257_irq_handler_thread,
					IRQF_TRIGGER_FALLING |
					IRQF_TRIGGER_RISING | IRQF_ONESHOT,
					bq2425x_chip_name[bq->chip], bq);
	if (ret) {
		dev_err(dev, "Failed to request IRQ #%d\n", client->irq);
		return ret;
	}

	return 0;
}