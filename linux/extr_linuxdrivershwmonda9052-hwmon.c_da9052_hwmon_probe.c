#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct device {int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct da9052_hwmon {int tsiref_mv; scalar_t__ tsiref; TYPE_1__* da9052; scalar_t__ tsi_as_adc; int /*<<< orphan*/  tsidone; int /*<<< orphan*/  hwmon_lock; } ;
struct TYPE_6__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9052_ADCCONT_ADCMODE ; 
 int /*<<< orphan*/  DA9052_ADC_CONT_REG ; 
 int /*<<< orphan*/  DA9052_IRQ_TSIREADY ; 
 int /*<<< orphan*/  DA9052_TSI_CONT_A_REG ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int PTR_ERR_OR_ZERO (struct device*) ; 
 int /*<<< orphan*/  da9052_free_irq (TYPE_1__*,int /*<<< orphan*/ ,struct da9052_hwmon*) ; 
 int /*<<< orphan*/  da9052_groups ; 
 int /*<<< orphan*/  da9052_reg_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9052_reg_write (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int da9052_request_irq (TYPE_1__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct da9052_hwmon*) ; 
 int /*<<< orphan*/  da9052_tsi_datardy_irq ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 TYPE_1__* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ device_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 struct device* devm_hwmon_device_register_with_groups (struct device*,char*,struct da9052_hwmon*,int /*<<< orphan*/ ) ; 
 struct da9052_hwmon* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ devm_regulator_get (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct da9052_hwmon*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int regulator_get_voltage (scalar_t__) ; 

__attribute__((used)) static int da9052_hwmon_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct da9052_hwmon *hwmon;
	struct device *hwmon_dev;
	int err;

	hwmon = devm_kzalloc(dev, sizeof(struct da9052_hwmon), GFP_KERNEL);
	if (!hwmon)
		return -ENOMEM;

	platform_set_drvdata(pdev, hwmon);

	mutex_init(&hwmon->hwmon_lock);
	hwmon->da9052 = dev_get_drvdata(pdev->dev.parent);

	init_completion(&hwmon->tsidone);

	hwmon->tsi_as_adc =
		device_property_read_bool(pdev->dev.parent, "dlg,tsi-as-adc");

	if (hwmon->tsi_as_adc) {
		hwmon->tsiref = devm_regulator_get(pdev->dev.parent, "tsiref");
		if (IS_ERR(hwmon->tsiref)) {
			err = PTR_ERR(hwmon->tsiref);
			dev_err(&pdev->dev, "failed to get tsiref: %d", err);
			return err;
		}

		err = regulator_enable(hwmon->tsiref);
		if (err)
			return err;

		hwmon->tsiref_mv = regulator_get_voltage(hwmon->tsiref);
		if (hwmon->tsiref_mv < 0) {
			err = hwmon->tsiref_mv;
			goto exit_regulator;
		}

		/* convert from microvolt (DT) to millivolt (hwmon) */
		hwmon->tsiref_mv /= 1000;

		/* TSIREF limits from datasheet */
		if (hwmon->tsiref_mv < 1800 || hwmon->tsiref_mv > 2600) {
			dev_err(hwmon->da9052->dev, "invalid TSIREF voltage: %d",
				hwmon->tsiref_mv);
			err = -ENXIO;
			goto exit_regulator;
		}

		/* disable touchscreen features */
		da9052_reg_write(hwmon->da9052, DA9052_TSI_CONT_A_REG, 0x00);

		/* Sample every 1ms */
		da9052_reg_update(hwmon->da9052, DA9052_ADC_CONT_REG,
					  DA9052_ADCCONT_ADCMODE,
					  DA9052_ADCCONT_ADCMODE);

		err = da9052_request_irq(hwmon->da9052, DA9052_IRQ_TSIREADY,
					 "tsiready-irq", da9052_tsi_datardy_irq,
					 hwmon);
		if (err) {
			dev_err(&pdev->dev, "Failed to register TSIRDY IRQ: %d",
				err);
			goto exit_regulator;
		}
	}

	hwmon_dev = devm_hwmon_device_register_with_groups(dev, "da9052",
							   hwmon,
							   da9052_groups);
	err = PTR_ERR_OR_ZERO(hwmon_dev);
	if (err)
		goto exit_irq;

	return 0;

exit_irq:
	if (hwmon->tsi_as_adc)
		da9052_free_irq(hwmon->da9052, DA9052_IRQ_TSIREADY, hwmon);
exit_regulator:
	if (hwmon->tsiref)
		regulator_disable(hwmon->tsiref);

	return err;
}