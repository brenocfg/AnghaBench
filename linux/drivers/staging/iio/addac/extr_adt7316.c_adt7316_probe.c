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
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char const* name; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct adt7316_bus {scalar_t__ irq; int (* write ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  client; } ;
struct adt7316_chip_info {int id; int dac_bits; int int_mask; int /*<<< orphan*/  config3; struct adt7316_bus bus; int /*<<< orphan*/  config1; int /*<<< orphan*/  ldac_pin; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADT7316_CONFIG1 ; 
 int /*<<< orphan*/  ADT7316_CONFIG3 ; 
 int /*<<< orphan*/  ADT7316_DA_EN_VIA_DAC_LDAC ; 
 int ADT7316_TEMP_INT_MASK ; 
 int ADT7316_VDD_INT_MASK ; 
 int ADT7516_AIN_INT_MASK ; 
 int /*<<< orphan*/  ADT7516_SEL_AIN3 ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int ID_ADT7316 ; 
 int ID_ADT7317 ; 
 int ID_ADT7516 ; 
 int ID_ADT7517 ; 
 int ID_ADT75XX ; 
 int ID_FAMILY_MASK ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adt7316_info ; 
 int adt7316_setup_irq (struct iio_dev*) ; 
 int /*<<< orphan*/  adt7516_info ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct adt7316_chip_info* iio_priv (struct iio_dev*) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int adt7316_probe(struct device *dev, struct adt7316_bus *bus,
		  const char *name)
{
	struct adt7316_chip_info *chip;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*chip));
	if (!indio_dev)
		return -ENOMEM;
	chip = iio_priv(indio_dev);
	/* this is only used for device removal purposes */
	dev_set_drvdata(dev, indio_dev);

	chip->bus = *bus;

	if (name[4] == '3')
		chip->id = ID_ADT7316 + (name[6] - '6');
	else if (name[4] == '5')
		chip->id = ID_ADT7516 + (name[6] - '6');
	else
		return -ENODEV;

	if (chip->id == ID_ADT7316 || chip->id == ID_ADT7516)
		chip->dac_bits = 12;
	else if (chip->id == ID_ADT7317 || chip->id == ID_ADT7517)
		chip->dac_bits = 10;
	else
		chip->dac_bits = 8;

	chip->ldac_pin = devm_gpiod_get_optional(dev, "adi,ldac",
						 GPIOD_OUT_LOW);
	if (IS_ERR(chip->ldac_pin)) {
		ret = PTR_ERR(chip->ldac_pin);
		dev_err(dev, "Failed to request ldac GPIO: %d\n", ret);
		return ret;
	}

	if (!chip->ldac_pin) {
		chip->config3 |= ADT7316_DA_EN_VIA_DAC_LDAC;
		if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
			chip->config1 |= ADT7516_SEL_AIN3;
	}
	chip->int_mask = ADT7316_TEMP_INT_MASK | ADT7316_VDD_INT_MASK;
	if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
		chip->int_mask |= ADT7516_AIN_INT_MASK;

	indio_dev->dev.parent = dev;
	if ((chip->id & ID_FAMILY_MASK) == ID_ADT75XX)
		indio_dev->info = &adt7516_info;
	else
		indio_dev->info = &adt7316_info;
	indio_dev->name = name;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (chip->bus.irq > 0) {
		ret = adt7316_setup_irq(indio_dev);
		if (ret)
			return ret;
	}

	ret = chip->bus.write(chip->bus.client, ADT7316_CONFIG1, chip->config1);
	if (ret)
		return -EIO;

	ret = chip->bus.write(chip->bus.client, ADT7316_CONFIG3, chip->config3);
	if (ret)
		return -EIO;

	ret = devm_iio_device_register(dev, indio_dev);
	if (ret)
		return ret;

	dev_info(dev, "%s temperature sensor, ADC and DAC registered.\n",
		 indio_dev->name);

	return 0;
}