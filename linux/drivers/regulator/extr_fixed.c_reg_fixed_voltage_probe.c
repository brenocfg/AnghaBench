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
struct regulator_config {scalar_t__ of_node; struct fixed_voltage_data* driver_data; int /*<<< orphan*/  init_data; struct device* dev; struct fixed_voltage_config* ena_gpiod; } ;
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int n_voltages; scalar_t__ fixed_uV; int /*<<< orphan*/ * name; void* supply_name; int /*<<< orphan*/  enable_time; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; } ;
struct fixed_voltage_data {TYPE_1__ desc; struct fixed_voltage_config* dev; struct fixed_voltage_config* enable_clock; } ;
struct fixed_voltage_config {int /*<<< orphan*/  init_data; scalar_t__ enabled_at_boot; scalar_t__ microvolts; scalar_t__ input_supply; int /*<<< orphan*/  startup_delay; scalar_t__ supply_name; } ;
struct fixed_dev_type {scalar_t__ has_enable_clock; } ;
typedef  enum gpiod_flags { ____Placeholder_gpiod_flags } gpiod_flags ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int GPIOD_FLAGS_BIT_NONEXCLUSIVE ; 
 int GPIOD_OUT_HIGH ; 
 int GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (struct fixed_voltage_config*) ; 
 int PTR_ERR (struct fixed_voltage_config*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct fixed_voltage_config* dev_get_platdata (struct device*) ; 
 struct fixed_voltage_config* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_kstrdup (struct device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct fixed_voltage_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct fixed_voltage_config* devm_regulator_register (struct device*,TYPE_1__*,struct regulator_config*) ; 
 int /*<<< orphan*/  fixed_voltage_clkenabled_ops ; 
 int /*<<< orphan*/  fixed_voltage_ops ; 
 struct fixed_voltage_config* gpiod_get_optional (struct device*,int /*<<< orphan*/ *,int) ; 
 struct fixed_dev_type* of_device_get_match_data (struct device*) ; 
 struct fixed_voltage_config* of_get_fixed_voltage_config (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct fixed_voltage_data*) ; 

__attribute__((used)) static int reg_fixed_voltage_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct fixed_voltage_config *config;
	struct fixed_voltage_data *drvdata;
	const struct fixed_dev_type *drvtype = of_device_get_match_data(dev);
	struct regulator_config cfg = { };
	enum gpiod_flags gflags;
	int ret;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(struct fixed_voltage_data),
			       GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	if (pdev->dev.of_node) {
		config = of_get_fixed_voltage_config(&pdev->dev,
						     &drvdata->desc);
		if (IS_ERR(config))
			return PTR_ERR(config);
	} else {
		config = dev_get_platdata(&pdev->dev);
	}

	if (!config)
		return -ENOMEM;

	drvdata->desc.name = devm_kstrdup(&pdev->dev,
					  config->supply_name,
					  GFP_KERNEL);
	if (drvdata->desc.name == NULL) {
		dev_err(&pdev->dev, "Failed to allocate supply name\n");
		return -ENOMEM;
	}
	drvdata->desc.type = REGULATOR_VOLTAGE;
	drvdata->desc.owner = THIS_MODULE;

	if (drvtype && drvtype->has_enable_clock) {
		drvdata->desc.ops = &fixed_voltage_clkenabled_ops;

		drvdata->enable_clock = devm_clk_get(dev, NULL);
		if (IS_ERR(drvdata->enable_clock)) {
			dev_err(dev, "Cant get enable-clock from devicetree\n");
			return -ENOENT;
		}
	} else {
		drvdata->desc.ops = &fixed_voltage_ops;
	}

	drvdata->desc.enable_time = config->startup_delay;

	if (config->input_supply) {
		drvdata->desc.supply_name = devm_kstrdup(&pdev->dev,
					    config->input_supply,
					    GFP_KERNEL);
		if (!drvdata->desc.supply_name) {
			dev_err(&pdev->dev,
				"Failed to allocate input supply\n");
			return -ENOMEM;
		}
	}

	if (config->microvolts)
		drvdata->desc.n_voltages = 1;

	drvdata->desc.fixed_uV = config->microvolts;

	/*
	 * The signal will be inverted by the GPIO core if flagged so in the
	 * decriptor.
	 */
	if (config->enabled_at_boot)
		gflags = GPIOD_OUT_HIGH;
	else
		gflags = GPIOD_OUT_LOW;

	/*
	 * Some fixed regulators share the enable line between two
	 * regulators which makes it necessary to get a handle on the
	 * same descriptor for two different consumers. This will get
	 * the GPIO descriptor, but only the first call will initialize
	 * it so any flags such as inversion or open drain will only
	 * be set up by the first caller and assumed identical on the
	 * next caller.
	 *
	 * FIXME: find a better way to deal with this.
	 */
	gflags |= GPIOD_FLAGS_BIT_NONEXCLUSIVE;

	/*
	 * Do not use devm* here: the regulator core takes over the
	 * lifecycle management of the GPIO descriptor.
	 */
	cfg.ena_gpiod = gpiod_get_optional(&pdev->dev, NULL, gflags);
	if (IS_ERR(cfg.ena_gpiod))
		return PTR_ERR(cfg.ena_gpiod);

	cfg.dev = &pdev->dev;
	cfg.init_data = config->init_data;
	cfg.driver_data = drvdata;
	cfg.of_node = pdev->dev.of_node;

	drvdata->dev = devm_regulator_register(&pdev->dev, &drvdata->desc,
					       &cfg);
	if (IS_ERR(drvdata->dev)) {
		ret = PTR_ERR(drvdata->dev);
		dev_err(&pdev->dev, "Failed to register regulator: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, drvdata);

	dev_dbg(&pdev->dev, "%s supplying %duV\n", drvdata->desc.name,
		drvdata->desc.fixed_uV);

	return 0;
}