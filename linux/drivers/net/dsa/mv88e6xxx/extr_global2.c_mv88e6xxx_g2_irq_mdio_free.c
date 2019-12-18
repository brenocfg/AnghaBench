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
struct mv88e6xxx_chip {TYPE_1__* info; } ;
struct mii_bus {int /*<<< orphan*/ * irq; } ;
struct TYPE_2__ {int num_internal_phys; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_dispose_mapping (int /*<<< orphan*/ ) ; 

void mv88e6xxx_g2_irq_mdio_free(struct mv88e6xxx_chip *chip,
				struct mii_bus *bus)
{
	int phy;

	for (phy = 0; phy < chip->info->num_internal_phys; phy++)
		irq_dispose_mapping(bus->irq[phy]);
}