#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct axp20x_dev {scalar_t__ variant; int irq_flags; TYPE_1__* dev; int /*<<< orphan*/  regmap_irqc; int /*<<< orphan*/  irq; int /*<<< orphan*/  nr_cells; int /*<<< orphan*/  cells; int /*<<< orphan*/  regmap_irq_chip; int /*<<< orphan*/  regmap; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 scalar_t__ AXP806_ID ; 
 int /*<<< orphan*/  AXP806_REG_ADDR_EXT ; 
 int /*<<< orphan*/  AXP806_REG_ADDR_EXT_ADDR_MASTER_MODE ; 
 int /*<<< orphan*/  AXP806_REG_ADDR_EXT_ADDR_SLAVE_MODE ; 
 int IRQF_ONESHOT ; 
 int IRQF_SHARED ; 
 struct axp20x_dev* axp20x_pm_power_off ; 
 scalar_t__ axp20x_power_off ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int mfd_add_devices (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pm_power_off ; 
 int regmap_add_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_del_irq_chip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int axp20x_device_probe(struct axp20x_dev *axp20x)
{
	int ret;

	/*
	 * The AXP806 supports either master/standalone or slave mode.
	 * Slave mode allows sharing the serial bus, even with multiple
	 * AXP806 which all have the same hardware address.
	 *
	 * This is done with extra "serial interface address extension",
	 * or AXP806_BUS_ADDR_EXT, and "register address extension", or
	 * AXP806_REG_ADDR_EXT, registers. The former is read-only, with
	 * 1 bit customizable at the factory, and 1 bit depending on the
	 * state of an external pin. The latter is writable. The device
	 * will only respond to operations to its other registers when
	 * the these device addressing bits (in the upper 4 bits of the
	 * registers) match.
	 *
	 * By default we support an AXP806 chained to an AXP809 in slave
	 * mode. Boards which use an AXP806 in master mode can set the
	 * property "x-powers,master-mode" to override the default.
	 */
	if (axp20x->variant == AXP806_ID) {
		if (of_property_read_bool(axp20x->dev->of_node,
					  "x-powers,master-mode") ||
		    of_property_read_bool(axp20x->dev->of_node,
					  "x-powers,self-working-mode"))
			regmap_write(axp20x->regmap, AXP806_REG_ADDR_EXT,
				     AXP806_REG_ADDR_EXT_ADDR_MASTER_MODE);
		else
			regmap_write(axp20x->regmap, AXP806_REG_ADDR_EXT,
				     AXP806_REG_ADDR_EXT_ADDR_SLAVE_MODE);
	}

	ret = regmap_add_irq_chip(axp20x->regmap, axp20x->irq,
			  IRQF_ONESHOT | IRQF_SHARED | axp20x->irq_flags,
			   -1, axp20x->regmap_irq_chip, &axp20x->regmap_irqc);
	if (ret) {
		dev_err(axp20x->dev, "failed to add irq chip: %d\n", ret);
		return ret;
	}

	ret = mfd_add_devices(axp20x->dev, -1, axp20x->cells,
			      axp20x->nr_cells, NULL, 0, NULL);

	if (ret) {
		dev_err(axp20x->dev, "failed to add MFD devices: %d\n", ret);
		regmap_del_irq_chip(axp20x->irq, axp20x->regmap_irqc);
		return ret;
	}

	if (!pm_power_off) {
		axp20x_pm_power_off = axp20x;
		pm_power_off = axp20x_power_off;
	}

	dev_info(axp20x->dev, "AXP20X driver loaded\n");

	return 0;
}