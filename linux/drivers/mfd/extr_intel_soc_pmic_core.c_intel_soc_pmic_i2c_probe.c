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
struct intel_soc_pmic_config {int irq_flags; int /*<<< orphan*/  n_cell_devs; int /*<<< orphan*/  cell_dev; int /*<<< orphan*/  irq_chip; int /*<<< orphan*/  regmap_config; } ;
struct intel_soc_pmic {int /*<<< orphan*/  irq_chip_data; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap; } ;
struct i2c_device_id {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_HANDLE (struct device*) ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
#define  BYT_CRC_HRV 129 
#define  CHT_CRC_HRV 128 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  crc_pwm_lookup ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct intel_soc_pmic*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct intel_soc_pmic* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int enable_irq_wake (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_add_lookup_table (int /*<<< orphan*/ *) ; 
 struct intel_soc_pmic_config intel_soc_pmic_config_byt_crc ; 
 struct intel_soc_pmic_config intel_soc_pmic_config_cht_crc ; 
 int mfd_add_devices (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panel_gpio_table ; 
 int /*<<< orphan*/  pwm_add_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_soc_pmic_i2c_probe(struct i2c_client *i2c,
				    const struct i2c_device_id *i2c_id)
{
	struct device *dev = &i2c->dev;
	struct intel_soc_pmic_config *config;
	struct intel_soc_pmic *pmic;
	unsigned long long hrv;
	acpi_status status;
	int ret;

	/*
	 * There are 2 different Crystal Cove PMICs a Bay Trail and Cherry
	 * Trail version, use _HRV to differentiate between the 2.
	 */
	status = acpi_evaluate_integer(ACPI_HANDLE(dev), "_HRV", NULL, &hrv);
	if (ACPI_FAILURE(status)) {
		dev_err(dev, "Failed to get PMIC hardware revision\n");
		return -ENODEV;
	}

	switch (hrv) {
	case BYT_CRC_HRV:
		config = &intel_soc_pmic_config_byt_crc;
		break;
	case CHT_CRC_HRV:
		config = &intel_soc_pmic_config_cht_crc;
		break;
	default:
		dev_warn(dev, "Unknown hardware rev %llu, assuming BYT\n", hrv);
		config = &intel_soc_pmic_config_byt_crc;
	}

	pmic = devm_kzalloc(dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic)
		return -ENOMEM;

	dev_set_drvdata(dev, pmic);

	pmic->regmap = devm_regmap_init_i2c(i2c, config->regmap_config);
	if (IS_ERR(pmic->regmap))
		return PTR_ERR(pmic->regmap);

	pmic->irq = i2c->irq;

	ret = regmap_add_irq_chip(pmic->regmap, pmic->irq,
				  config->irq_flags | IRQF_ONESHOT,
				  0, config->irq_chip,
				  &pmic->irq_chip_data);
	if (ret)
		return ret;

	ret = enable_irq_wake(pmic->irq);
	if (ret)
		dev_warn(dev, "Can't enable IRQ as wake source: %d\n", ret);

	/* Add lookup table binding for Panel Control to the GPIO Chip */
	gpiod_add_lookup_table(&panel_gpio_table);

	/* Add lookup table for crc-pwm */
	pwm_add_table(crc_pwm_lookup, ARRAY_SIZE(crc_pwm_lookup));

	ret = mfd_add_devices(dev, -1, config->cell_dev,
			      config->n_cell_devs, NULL, 0,
			      regmap_irq_get_domain(pmic->irq_chip_data));
	if (ret)
		goto err_del_irq_chip;

	return 0;

err_del_irq_chip:
	regmap_del_irq_chip(pmic->irq, pmic->irq_chip_data);
	return ret;
}