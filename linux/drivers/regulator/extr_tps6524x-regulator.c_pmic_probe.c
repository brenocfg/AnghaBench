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
struct tps6524x {TYPE_1__* desc; int /*<<< orphan*/  lock; struct spi_device* spi; struct device* dev; } ;
struct supply_info {int /*<<< orphan*/  voltages; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct spi_device {struct device dev; } ;
struct regulator_init_data {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {struct tps6524x* driver_data; struct regulator_init_data* init_data; struct device* dev; } ;
struct TYPE_2__ {int id; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; int /*<<< orphan*/ * ops; int /*<<< orphan*/  volt_table; int /*<<< orphan*/  n_voltages; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int N_REGULATORS ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct regulator_init_data* dev_get_platdata (struct device*) ; 
 struct tps6524x* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (struct device*,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  memset (struct tps6524x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_ops ; 
 int /*<<< orphan*/  spi_set_drvdata (struct spi_device*,struct tps6524x*) ; 
 struct supply_info* supply_info ; 

__attribute__((used)) static int pmic_probe(struct spi_device *spi)
{
	struct tps6524x *hw;
	struct device *dev = &spi->dev;
	const struct supply_info *info = supply_info;
	struct regulator_init_data *init_data;
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	int i;

	init_data = dev_get_platdata(dev);
	if (!init_data) {
		dev_err(dev, "could not find regulator platform data\n");
		return -EINVAL;
	}

	hw = devm_kzalloc(&spi->dev, sizeof(struct tps6524x), GFP_KERNEL);
	if (!hw)
		return -ENOMEM;

	spi_set_drvdata(spi, hw);

	memset(hw, 0, sizeof(struct tps6524x));
	hw->dev = dev;
	hw->spi = spi;
	mutex_init(&hw->lock);

	for (i = 0; i < N_REGULATORS; i++, info++, init_data++) {
		hw->desc[i].name	= info->name;
		hw->desc[i].id		= i;
		hw->desc[i].n_voltages	= info->n_voltages;
		hw->desc[i].volt_table	= info->voltages;
		hw->desc[i].ops		= &regulator_ops;
		hw->desc[i].type	= REGULATOR_VOLTAGE;
		hw->desc[i].owner	= THIS_MODULE;

		config.dev = dev;
		config.init_data = init_data;
		config.driver_data = hw;

		rdev = devm_regulator_register(dev, &hw->desc[i], &config);
		if (IS_ERR(rdev))
			return PTR_ERR(rdev);
	}

	return 0;
}