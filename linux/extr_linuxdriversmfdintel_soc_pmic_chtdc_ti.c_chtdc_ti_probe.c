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
struct intel_soc_pmic {int /*<<< orphan*/  irq_chip_data; int /*<<< orphan*/  irq; int /*<<< orphan*/  regmap; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chtdc_ti_dev ; 
 int /*<<< orphan*/  chtdc_ti_irq_chip ; 
 int /*<<< orphan*/  chtdc_ti_regmap_config ; 
 struct intel_soc_pmic* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_mfd_add_devices (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_regmap_add_irq_chip (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct intel_soc_pmic*) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chtdc_ti_probe(struct i2c_client *i2c)
{
	struct device *dev = &i2c->dev;
	struct intel_soc_pmic *pmic;
	int ret;

	pmic = devm_kzalloc(dev, sizeof(*pmic), GFP_KERNEL);
	if (!pmic)
		return -ENOMEM;

	i2c_set_clientdata(i2c, pmic);

	pmic->regmap = devm_regmap_init_i2c(i2c, &chtdc_ti_regmap_config);
	if (IS_ERR(pmic->regmap))
		return PTR_ERR(pmic->regmap);
	pmic->irq = i2c->irq;

	ret = devm_regmap_add_irq_chip(dev, pmic->regmap, pmic->irq,
				       IRQF_ONESHOT, 0,
				       &chtdc_ti_irq_chip,
				       &pmic->irq_chip_data);
	if (ret)
		return ret;

	return devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE, chtdc_ti_dev,
				    ARRAY_SIZE(chtdc_ti_dev), NULL, 0,
				    regmap_irq_get_domain(pmic->irq_chip_data));
}