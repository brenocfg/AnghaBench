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
typedef  int u32 ;
struct regulator_init_data {char* supply_regulator; } ;
struct regulator_dev {int dummy; } ;
struct regulator_desc {int n_voltages; int min_uV; int uV_step; int linear_min_sel; int vsel_reg; int vsel_mask; int min_dropout_uV; int enable_reg; int /*<<< orphan*/  name; int /*<<< orphan*/  enable_mask; TYPE_1__* ops; int /*<<< orphan*/  owner; int /*<<< orphan*/  type; } ;
struct regulator_config {struct regulator_dev* regmap; struct device_node* of_node; struct anatop_regulator* driver_data; struct regulator_init_data* init_data; struct device* dev; } ;
typedef  struct regulator_dev regmap ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct anatop_regulator {int delay_reg; int delay_bit_width; int delay_bit_shift; int sel; int bypass; struct regulator_desc rdesc; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_enabled; int /*<<< orphan*/  disable; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int LDO_FET_FULL_ON ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  REGULATOR_VOLTAGE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_1__ anatop_core_rops ; 
 TYPE_1__ anatop_rops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct anatop_regulator* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct regulator_dev* devm_regulator_register (struct device*,struct regulator_desc*,struct regulator_config*) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 struct regulator_init_data* of_get_regulator_init_data (struct device*,struct device_node*,struct regulator_desc*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_string (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 
 int regmap_read (struct regulator_dev*,int,int*) ; 
 int /*<<< orphan*/  regulator_disable_regmap ; 
 int /*<<< orphan*/  regulator_enable_regmap ; 
 int /*<<< orphan*/  regulator_is_enabled_regmap ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 struct regulator_dev* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int anatop_regulator_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct device_node *anatop_np;
	struct regulator_desc *rdesc;
	struct regulator_dev *rdev;
	struct anatop_regulator *sreg;
	struct regulator_init_data *initdata;
	struct regulator_config config = { };
	struct regmap *regmap;
	u32 control_reg;
	u32 vol_bit_shift;
	u32 vol_bit_width;
	u32 min_bit_val;
	u32 min_voltage;
	u32 max_voltage;
	int ret = 0;
	u32 val;

	sreg = devm_kzalloc(dev, sizeof(*sreg), GFP_KERNEL);
	if (!sreg)
		return -ENOMEM;

	rdesc = &sreg->rdesc;
	rdesc->type = REGULATOR_VOLTAGE;
	rdesc->owner = THIS_MODULE;

	of_property_read_string(np, "regulator-name", &rdesc->name);
	if (!rdesc->name) {
		dev_err(dev, "failed to get a regulator-name\n");
		return -EINVAL;
	}

	initdata = of_get_regulator_init_data(dev, np, rdesc);
	if (!initdata)
		return -ENOMEM;

	initdata->supply_regulator = "vin";

	anatop_np = of_get_parent(np);
	if (!anatop_np)
		return -ENODEV;
	regmap = syscon_node_to_regmap(anatop_np);
	of_node_put(anatop_np);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret = of_property_read_u32(np, "anatop-reg-offset", &control_reg);
	if (ret) {
		dev_err(dev, "no anatop-reg-offset property set\n");
		return ret;
	}
	ret = of_property_read_u32(np, "anatop-vol-bit-width", &vol_bit_width);
	if (ret) {
		dev_err(dev, "no anatop-vol-bit-width property set\n");
		return ret;
	}
	ret = of_property_read_u32(np, "anatop-vol-bit-shift", &vol_bit_shift);
	if (ret) {
		dev_err(dev, "no anatop-vol-bit-shift property set\n");
		return ret;
	}
	ret = of_property_read_u32(np, "anatop-min-bit-val", &min_bit_val);
	if (ret) {
		dev_err(dev, "no anatop-min-bit-val property set\n");
		return ret;
	}
	ret = of_property_read_u32(np, "anatop-min-voltage", &min_voltage);
	if (ret) {
		dev_err(dev, "no anatop-min-voltage property set\n");
		return ret;
	}
	ret = of_property_read_u32(np, "anatop-max-voltage", &max_voltage);
	if (ret) {
		dev_err(dev, "no anatop-max-voltage property set\n");
		return ret;
	}

	/* read LDO ramp up setting, only for core reg */
	of_property_read_u32(np, "anatop-delay-reg-offset",
			     &sreg->delay_reg);
	of_property_read_u32(np, "anatop-delay-bit-width",
			     &sreg->delay_bit_width);
	of_property_read_u32(np, "anatop-delay-bit-shift",
			     &sreg->delay_bit_shift);

	rdesc->n_voltages = (max_voltage - min_voltage) / 25000 + 1
			    + min_bit_val;
	rdesc->min_uV = min_voltage;
	rdesc->uV_step = 25000;
	rdesc->linear_min_sel = min_bit_val;
	rdesc->vsel_reg = control_reg;
	rdesc->vsel_mask = ((1 << vol_bit_width) - 1) << vol_bit_shift;
	rdesc->min_dropout_uV = 125000;

	config.dev = &pdev->dev;
	config.init_data = initdata;
	config.driver_data = sreg;
	config.of_node = pdev->dev.of_node;
	config.regmap = regmap;

	/* Only core regulators have the ramp up delay configuration. */
	if (control_reg && sreg->delay_bit_width) {
		rdesc->ops = &anatop_core_rops;

		ret = regmap_read(config.regmap, rdesc->vsel_reg, &val);
		if (ret) {
			dev_err(dev, "failed to read initial state\n");
			return ret;
		}

		sreg->sel = (val & rdesc->vsel_mask) >> vol_bit_shift;
		if (sreg->sel == LDO_FET_FULL_ON) {
			sreg->sel = 0;
			sreg->bypass = true;
		}

		/*
		 * In case vddpu was disabled by the bootloader, we need to set
		 * a sane default until imx6-cpufreq was probed and changes the
		 * voltage to the correct value. In this case we set 1.25V.
		 */
		if (!sreg->sel && !strcmp(rdesc->name, "vddpu"))
			sreg->sel = 22;

		/* set the default voltage of the pcie phy to be 1.100v */
		if (!sreg->sel && !strcmp(rdesc->name, "vddpcie"))
			sreg->sel = 0x10;

		if (!sreg->bypass && !sreg->sel) {
			dev_err(&pdev->dev, "Failed to read a valid default voltage selector.\n");
			return -EINVAL;
		}
	} else {
		u32 enable_bit;

		rdesc->ops = &anatop_rops;

		if (!of_property_read_u32(np, "anatop-enable-bit",
					  &enable_bit)) {
			anatop_rops.enable  = regulator_enable_regmap;
			anatop_rops.disable = regulator_disable_regmap;
			anatop_rops.is_enabled = regulator_is_enabled_regmap;

			rdesc->enable_reg = control_reg;
			rdesc->enable_mask = BIT(enable_bit);
		}
	}

	/* register regulator */
	rdev = devm_regulator_register(dev, rdesc, &config);
	if (IS_ERR(rdev)) {
		dev_err(dev, "failed to register %s\n",
			rdesc->name);
		return PTR_ERR(rdev);
	}

	platform_set_drvdata(pdev, rdev);

	return 0;
}