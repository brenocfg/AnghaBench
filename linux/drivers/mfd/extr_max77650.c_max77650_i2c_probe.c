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
struct regmap_irq_chip_data {int dummy; } ;
struct regmap {int dummy; } ;
struct irq_domain {int dummy; } ;
struct device {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  irq; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
#define  MAX77650_CID_77650A 131 
#define  MAX77650_CID_77650C 130 
#define  MAX77650_CID_77651A 129 
#define  MAX77650_CID_77651B 128 
 int MAX77650_CID_BITS (unsigned int) ; 
 int /*<<< orphan*/  MAX77650_REG_CID ; 
 int /*<<< orphan*/  MAX77650_REG_CNFG_GLBL ; 
 int /*<<< orphan*/  MAX77650_SBIA_LPM_DISABLED ; 
 int /*<<< orphan*/  MAX77650_SBIA_LPM_MASK ; 
 int /*<<< orphan*/  PLATFORM_DEVID_NONE ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_mfd_add_devices (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct irq_domain*) ; 
 int devm_regmap_add_irq_chip (struct device*,struct regmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct regmap_irq_chip_data**) ; 
 struct regmap* devm_regmap_init_i2c (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max77650_cells ; 
 int /*<<< orphan*/  max77650_irq_chip ; 
 int /*<<< orphan*/  max77650_regmap_config ; 
 struct irq_domain* regmap_irq_get_domain (struct regmap_irq_chip_data*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77650_i2c_probe(struct i2c_client *i2c)
{
	struct regmap_irq_chip_data *irq_data;
	struct device *dev = &i2c->dev;
	struct irq_domain *domain;
	struct regmap *map;
	unsigned int val;
	int rv, id;

	map = devm_regmap_init_i2c(i2c, &max77650_regmap_config);
	if (IS_ERR(map)) {
		dev_err(dev, "Unable to initialise I2C Regmap\n");
		return PTR_ERR(map);
	}

	rv = regmap_read(map, MAX77650_REG_CID, &val);
	if (rv) {
		dev_err(dev, "Unable to read Chip ID\n");
		return rv;
	}

	id = MAX77650_CID_BITS(val);
	switch (id) {
	case MAX77650_CID_77650A:
	case MAX77650_CID_77650C:
	case MAX77650_CID_77651A:
	case MAX77650_CID_77651B:
		break;
	default:
		dev_err(dev, "Chip not supported - ID: 0x%02x\n", id);
		return -ENODEV;
	}

	/*
	 * This IC has a low-power mode which reduces the quiescent current
	 * consumption to ~5.6uA but is only suitable for systems consuming
	 * less than ~2mA. Since this is not likely the case even on
	 * linux-based wearables - keep the chip in normal power mode.
	 */
	rv = regmap_update_bits(map,
				MAX77650_REG_CNFG_GLBL,
				MAX77650_SBIA_LPM_MASK,
				MAX77650_SBIA_LPM_DISABLED);
	if (rv) {
		dev_err(dev, "Unable to change the power mode\n");
		return rv;
	}

	rv = devm_regmap_add_irq_chip(dev, map, i2c->irq,
				      IRQF_ONESHOT | IRQF_SHARED, 0,
				      &max77650_irq_chip, &irq_data);
	if (rv) {
		dev_err(dev, "Unable to add Regmap IRQ chip\n");
		return rv;
	}

	domain = regmap_irq_get_domain(irq_data);

	return devm_mfd_add_devices(dev, PLATFORM_DEVID_NONE,
				    max77650_cells, ARRAY_SIZE(max77650_cells),
				    NULL, 0, domain);
}