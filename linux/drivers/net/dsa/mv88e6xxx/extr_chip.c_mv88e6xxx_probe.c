#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mv88e6xxx_info {scalar_t__ g2_irqs; TYPE_2__* ops; } ;
struct mv88e6xxx_chip {int irq; struct mv88e6xxx_info const* info; int /*<<< orphan*/  eeprom_len; scalar_t__ reset; } ;
struct device {struct device_node* of_node; struct dsa_mv88e6xxx_pdata* platform_data; } ;
struct mdio_device {int /*<<< orphan*/  addr; int /*<<< orphan*/  bus; struct device dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** netdev; int /*<<< orphan*/ * port_names; } ;
struct dsa_mv88e6xxx_pdata {int enabled_ports; int irq; TYPE_3__* netdev; int /*<<< orphan*/  eeprom_len; TYPE_1__ cd; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {scalar_t__ get_eeprom; } ;

/* Variables and functions */
 int DSA_MAX_PORTS ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  dev_put (TYPE_3__*) ; 
 scalar_t__ devm_gpiod_get_optional (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct mv88e6xxx_chip* mv88e6xxx_alloc_chip (struct device*) ; 
 int mv88e6xxx_detect (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_atu_prob_irq_free (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_atu_prob_irq_setup (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_irq_free (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_irq_setup (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_vtu_prob_irq_free (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g1_vtu_prob_irq_setup (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g2_irq_free (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_g2_irq_setup (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_irq_poll_free (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_irq_poll_setup (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_mdios_register (struct mv88e6xxx_chip*,struct device_node*) ; 
 int /*<<< orphan*/  mv88e6xxx_mdios_unregister (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_phy_init (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_lock (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_reg_unlock (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_register_switch (struct mv88e6xxx_chip*) ; 
 int mv88e6xxx_smi_init (struct mv88e6xxx_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mv88e6xxx_switch_reset (struct mv88e6xxx_chip*) ; 
 struct mv88e6xxx_info* of_device_get_match_data (struct device*) ; 
 int of_irq_get (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct mv88e6xxx_info* pdata_device_get_match_data (struct device*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mv88e6xxx_probe(struct mdio_device *mdiodev)
{
	struct dsa_mv88e6xxx_pdata *pdata = mdiodev->dev.platform_data;
	const struct mv88e6xxx_info *compat_info = NULL;
	struct device *dev = &mdiodev->dev;
	struct device_node *np = dev->of_node;
	struct mv88e6xxx_chip *chip;
	int port;
	int err;

	if (!np && !pdata)
		return -EINVAL;

	if (np)
		compat_info = of_device_get_match_data(dev);

	if (pdata) {
		compat_info = pdata_device_get_match_data(dev);

		if (!pdata->netdev)
			return -EINVAL;

		for (port = 0; port < DSA_MAX_PORTS; port++) {
			if (!(pdata->enabled_ports & (1 << port)))
				continue;
			if (strcmp(pdata->cd.port_names[port], "cpu"))
				continue;
			pdata->cd.netdev[port] = &pdata->netdev->dev;
			break;
		}
	}

	if (!compat_info)
		return -EINVAL;

	chip = mv88e6xxx_alloc_chip(dev);
	if (!chip) {
		err = -ENOMEM;
		goto out;
	}

	chip->info = compat_info;

	err = mv88e6xxx_smi_init(chip, mdiodev->bus, mdiodev->addr);
	if (err)
		goto out;

	chip->reset = devm_gpiod_get_optional(dev, "reset", GPIOD_OUT_LOW);
	if (IS_ERR(chip->reset)) {
		err = PTR_ERR(chip->reset);
		goto out;
	}
	if (chip->reset)
		usleep_range(1000, 2000);

	err = mv88e6xxx_detect(chip);
	if (err)
		goto out;

	mv88e6xxx_phy_init(chip);

	if (chip->info->ops->get_eeprom) {
		if (np)
			of_property_read_u32(np, "eeprom-length",
					     &chip->eeprom_len);
		else
			chip->eeprom_len = pdata->eeprom_len;
	}

	mv88e6xxx_reg_lock(chip);
	err = mv88e6xxx_switch_reset(chip);
	mv88e6xxx_reg_unlock(chip);
	if (err)
		goto out;

	if (np) {
		chip->irq = of_irq_get(np, 0);
		if (chip->irq == -EPROBE_DEFER) {
			err = chip->irq;
			goto out;
		}
	}

	if (pdata)
		chip->irq = pdata->irq;

	/* Has to be performed before the MDIO bus is created, because
	 * the PHYs will link their interrupts to these interrupt
	 * controllers
	 */
	mv88e6xxx_reg_lock(chip);
	if (chip->irq > 0)
		err = mv88e6xxx_g1_irq_setup(chip);
	else
		err = mv88e6xxx_irq_poll_setup(chip);
	mv88e6xxx_reg_unlock(chip);

	if (err)
		goto out;

	if (chip->info->g2_irqs > 0) {
		err = mv88e6xxx_g2_irq_setup(chip);
		if (err)
			goto out_g1_irq;
	}

	err = mv88e6xxx_g1_atu_prob_irq_setup(chip);
	if (err)
		goto out_g2_irq;

	err = mv88e6xxx_g1_vtu_prob_irq_setup(chip);
	if (err)
		goto out_g1_atu_prob_irq;

	err = mv88e6xxx_mdios_register(chip, np);
	if (err)
		goto out_g1_vtu_prob_irq;

	err = mv88e6xxx_register_switch(chip);
	if (err)
		goto out_mdio;

	return 0;

out_mdio:
	mv88e6xxx_mdios_unregister(chip);
out_g1_vtu_prob_irq:
	mv88e6xxx_g1_vtu_prob_irq_free(chip);
out_g1_atu_prob_irq:
	mv88e6xxx_g1_atu_prob_irq_free(chip);
out_g2_irq:
	if (chip->info->g2_irqs > 0)
		mv88e6xxx_g2_irq_free(chip);
out_g1_irq:
	if (chip->irq > 0)
		mv88e6xxx_g1_irq_free(chip);
	else
		mv88e6xxx_irq_poll_free(chip);
out:
	if (pdata)
		dev_put(pdata->netdev);

	return err;
}