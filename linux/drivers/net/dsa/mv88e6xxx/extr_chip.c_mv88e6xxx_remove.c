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
struct mv88e6xxx_chip {scalar_t__ irq; TYPE_1__* info; } ;
struct mdio_device {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct mv88e6xxx_chip* priv; } ;
struct TYPE_2__ {scalar_t__ g2_irqs; scalar_t__ ptp_support; } ;

/* Variables and functions */
 struct dsa_switch* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_atu_prob_irq_free (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_irq_free (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g1_vtu_prob_irq_free (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_g2_irq_free (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_hwtstamp_free (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_irq_poll_free (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_mdios_unregister (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_phy_destroy (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_ptp_free (struct mv88e6xxx_chip*) ; 
 int /*<<< orphan*/  mv88e6xxx_unregister_switch (struct mv88e6xxx_chip*) ; 

__attribute__((used)) static void mv88e6xxx_remove(struct mdio_device *mdiodev)
{
	struct dsa_switch *ds = dev_get_drvdata(&mdiodev->dev);
	struct mv88e6xxx_chip *chip = ds->priv;

	if (chip->info->ptp_support) {
		mv88e6xxx_hwtstamp_free(chip);
		mv88e6xxx_ptp_free(chip);
	}

	mv88e6xxx_phy_destroy(chip);
	mv88e6xxx_unregister_switch(chip);
	mv88e6xxx_mdios_unregister(chip);

	mv88e6xxx_g1_vtu_prob_irq_free(chip);
	mv88e6xxx_g1_atu_prob_irq_free(chip);

	if (chip->info->g2_irqs > 0)
		mv88e6xxx_g2_irq_free(chip);

	if (chip->irq > 0)
		mv88e6xxx_g1_irq_free(chip);
	else
		mv88e6xxx_irq_poll_free(chip);
}