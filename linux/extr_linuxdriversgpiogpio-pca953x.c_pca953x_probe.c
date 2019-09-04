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
typedef  int /*<<< orphan*/  u32 ;
struct regulator {int dummy; } ;
struct pca953x_platform_data {int irq_base; int gpio_base; int (* setup ) (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  context; int /*<<< orphan*/  names; int /*<<< orphan*/  invert; } ;
struct TYPE_2__ {int ngpio; int /*<<< orphan*/  base; } ;
struct pca953x_chip {int gpio_start; uintptr_t driver_data; struct regulator* regulator; TYPE_1__ gpio_chip; int /*<<< orphan*/  read_regs; int /*<<< orphan*/  write_regs; int /*<<< orphan*/  i2c_lock; struct i2c_client* client; int /*<<< orphan*/  names; } ;
struct i2c_device_id {uintptr_t driver_data; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; int /*<<< orphan*/  adapter; } ;
typedef  struct regulator gpio_desc ;
struct acpi_device_id {uintptr_t driver_data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct regulator*) ; 
 scalar_t__ PCA953X_TYPE ; 
 scalar_t__ PCA_CHIP_TYPE (int) ; 
 int PCA_GPIO_MASK ; 
 int PTR_ERR (struct regulator*) ; 
 struct acpi_device_id* acpi_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct pca953x_platform_data* dev_get_platdata (struct device*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 int device_pca953x_init (struct pca953x_chip*,int /*<<< orphan*/ ) ; 
 int device_pca957x_init (struct pca953x_chip*,int /*<<< orphan*/ ) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct pca953x_chip*) ; 
 struct regulator* devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct pca953x_chip* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regulator* devm_regulator_get (struct device*,char*) ; 
 int /*<<< orphan*/  i2c_adapter_depth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct pca953x_chip*) ; 
 int /*<<< orphan*/  lockdep_set_subclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  pca953x_acpi_ids ; 
 int pca953x_irq_setup (struct pca953x_chip*,int) ; 
 int /*<<< orphan*/  pca953x_read_regs_16 ; 
 int /*<<< orphan*/  pca953x_read_regs_24 ; 
 int /*<<< orphan*/  pca953x_read_regs_8 ; 
 int /*<<< orphan*/  pca953x_setup_gpio (struct pca953x_chip*,int) ; 
 int /*<<< orphan*/  pca953x_write_regs_16 ; 
 int /*<<< orphan*/  pca953x_write_regs_24 ; 
 int /*<<< orphan*/  pca953x_write_regs_8 ; 
 int /*<<< orphan*/  pca957x_write_regs_16 ; 
 int /*<<< orphan*/  regulator_disable (struct regulator*) ; 
 int regulator_enable (struct regulator*) ; 
 int stub1 (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pca953x_probe(struct i2c_client *client,
				   const struct i2c_device_id *i2c_id)
{
	struct pca953x_platform_data *pdata;
	struct pca953x_chip *chip;
	int irq_base = 0;
	int ret;
	u32 invert = 0;
	struct regulator *reg;

	chip = devm_kzalloc(&client->dev,
			sizeof(struct pca953x_chip), GFP_KERNEL);
	if (chip == NULL)
		return -ENOMEM;

	pdata = dev_get_platdata(&client->dev);
	if (pdata) {
		irq_base = pdata->irq_base;
		chip->gpio_start = pdata->gpio_base;
		invert = pdata->invert;
		chip->names = pdata->names;
	} else {
		struct gpio_desc *reset_gpio;

		chip->gpio_start = -1;
		irq_base = 0;

		/*
		 * See if we need to de-assert a reset pin.
		 *
		 * There is no known ACPI-enabled platforms that are
		 * using "reset" GPIO. Otherwise any of those platform
		 * must use _DSD method with corresponding property.
		 */
		reset_gpio = devm_gpiod_get_optional(&client->dev, "reset",
						     GPIOD_OUT_LOW);
		if (IS_ERR(reset_gpio))
			return PTR_ERR(reset_gpio);
	}

	chip->client = client;

	reg = devm_regulator_get(&client->dev, "vcc");
	if (IS_ERR(reg)) {
		ret = PTR_ERR(reg);
		if (ret != -EPROBE_DEFER)
			dev_err(&client->dev, "reg get err: %d\n", ret);
		return ret;
	}
	ret = regulator_enable(reg);
	if (ret) {
		dev_err(&client->dev, "reg en err: %d\n", ret);
		return ret;
	}
	chip->regulator = reg;

	if (i2c_id) {
		chip->driver_data = i2c_id->driver_data;
	} else {
		const struct acpi_device_id *acpi_id;
		struct device *dev = &client->dev;

		chip->driver_data = (uintptr_t)of_device_get_match_data(dev);
		if (!chip->driver_data) {
			acpi_id = acpi_match_device(pca953x_acpi_ids, dev);
			if (!acpi_id) {
				ret = -ENODEV;
				goto err_exit;
			}

			chip->driver_data = acpi_id->driver_data;
		}
	}

	mutex_init(&chip->i2c_lock);
	/*
	 * In case we have an i2c-mux controlled by a GPIO provided by an
	 * expander using the same driver higher on the device tree, read the
	 * i2c adapter nesting depth and use the retrieved value as lockdep
	 * subclass for chip->i2c_lock.
	 *
	 * REVISIT: This solution is not complete. It protects us from lockdep
	 * false positives when the expander controlling the i2c-mux is on
	 * a different level on the device tree, but not when it's on the same
	 * level on a different branch (in which case the subclass number
	 * would be the same).
	 *
	 * TODO: Once a correct solution is developed, a similar fix should be
	 * applied to all other i2c-controlled GPIO expanders (and potentially
	 * regmap-i2c).
	 */
	lockdep_set_subclass(&chip->i2c_lock,
			     i2c_adapter_depth(client->adapter));

	/* initialize cached registers from their original values.
	 * we can't share this chip with another i2c master.
	 */
	pca953x_setup_gpio(chip, chip->driver_data & PCA_GPIO_MASK);

	if (chip->gpio_chip.ngpio <= 8) {
		chip->write_regs = pca953x_write_regs_8;
		chip->read_regs = pca953x_read_regs_8;
	} else if (chip->gpio_chip.ngpio >= 24) {
		chip->write_regs = pca953x_write_regs_24;
		chip->read_regs = pca953x_read_regs_24;
	} else {
		if (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE)
			chip->write_regs = pca953x_write_regs_16;
		else
			chip->write_regs = pca957x_write_regs_16;
		chip->read_regs = pca953x_read_regs_16;
	}

	if (PCA_CHIP_TYPE(chip->driver_data) == PCA953X_TYPE)
		ret = device_pca953x_init(chip, invert);
	else
		ret = device_pca957x_init(chip, invert);
	if (ret)
		goto err_exit;

	ret = devm_gpiochip_add_data(&client->dev, &chip->gpio_chip, chip);
	if (ret)
		goto err_exit;

	ret = pca953x_irq_setup(chip, irq_base);
	if (ret)
		goto err_exit;

	if (pdata && pdata->setup) {
		ret = pdata->setup(client, chip->gpio_chip.base,
				chip->gpio_chip.ngpio, pdata->context);
		if (ret < 0)
			dev_warn(&client->dev, "setup failed, %d\n", ret);
	}

	i2c_set_clientdata(client, chip);
	return 0;

err_exit:
	regulator_disable(chip->regulator);
	return ret;
}