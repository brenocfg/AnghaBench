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
struct ti_lmu_data {int /*<<< orphan*/  num_cells; int /*<<< orphan*/  cells; int /*<<< orphan*/  max_register; } ;
struct ti_lmu {struct device* dev; int /*<<< orphan*/  notifier; int /*<<< orphan*/  en_gpio; int /*<<< orphan*/  regmap; } ;
struct regmap_config {int reg_bits; int val_bits; int /*<<< orphan*/  max_register; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int /*<<< orphan*/  driver_data; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct i2c_client {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct ti_lmu*) ; 
 int /*<<< orphan*/  devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct ti_lmu* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct ti_lmu*) ; 
 int /*<<< orphan*/  memset (struct regmap_config*,int /*<<< orphan*/ ,int) ; 
 struct ti_lmu_data* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  ti_lmu_disable_hw ; 
 int ti_lmu_enable_hw (struct ti_lmu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ti_lmu_probe(struct i2c_client *cl, const struct i2c_device_id *id)
{
	struct device *dev = &cl->dev;
	const struct ti_lmu_data *data;
	struct regmap_config regmap_cfg;
	struct ti_lmu *lmu;
	int ret;

	/*
	 * Get device specific data from of_match table.
	 * This data is defined by using TI_LMU_DATA() macro.
	 */
	data = of_device_get_match_data(dev);
	if (!data)
		return -ENODEV;

	lmu = devm_kzalloc(dev, sizeof(*lmu), GFP_KERNEL);
	if (!lmu)
		return -ENOMEM;

	lmu->dev = &cl->dev;

	/* Setup regmap */
	memset(&regmap_cfg, 0, sizeof(struct regmap_config));
	regmap_cfg.reg_bits = 8;
	regmap_cfg.val_bits = 8;
	regmap_cfg.name = id->name;
	regmap_cfg.max_register = data->max_register;

	lmu->regmap = devm_regmap_init_i2c(cl, &regmap_cfg);
	if (IS_ERR(lmu->regmap))
		return PTR_ERR(lmu->regmap);

	/* HW enable pin control and additional power up sequence if required */
	lmu->en_gpio = devm_gpiod_get_optional(dev, "enable", GPIOD_OUT_HIGH);
	if (IS_ERR(lmu->en_gpio)) {
		ret = PTR_ERR(lmu->en_gpio);
		dev_err(dev, "Can not request enable GPIO: %d\n", ret);
		return ret;
	}

	ret = ti_lmu_enable_hw(lmu, id->driver_data);
	if (ret)
		return ret;

	ret = devm_add_action_or_reset(dev, ti_lmu_disable_hw, lmu);
	if (ret)
		return ret;

	/*
	 * Fault circuit(open/short) can be detected by ti-lmu-fault-monitor.
	 * After fault detection is done, some devices should re-initialize
	 * configuration. The notifier enables such kind of handling.
	 */
	BLOCKING_INIT_NOTIFIER_HEAD(&lmu->notifier);

	i2c_set_clientdata(cl, lmu);

	return devm_mfd_add_devices(lmu->dev, 0, data->cells,
				    data->num_cells, NULL, 0, NULL);
}