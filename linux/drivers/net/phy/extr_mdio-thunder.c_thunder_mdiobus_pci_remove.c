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
struct thunder_mdiobus_nexus {struct cavium_mdiobus** buses; } ;
struct pci_dev {int dummy; } ;
struct cavium_mdiobus {scalar_t__ register_base; int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct cavium_mdiobus**) ; 
 scalar_t__ SMI_EN ; 
 int /*<<< orphan*/  mdiobus_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oct_mdio_writeq (int /*<<< orphan*/ ,scalar_t__) ; 
 struct thunder_mdiobus_nexus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void thunder_mdiobus_pci_remove(struct pci_dev *pdev)
{
	int i;
	struct thunder_mdiobus_nexus *nexus = pci_get_drvdata(pdev);

	for (i = 0; i < ARRAY_SIZE(nexus->buses); i++) {
		struct cavium_mdiobus *bus = nexus->buses[i];

		if (!bus)
			continue;

		mdiobus_unregister(bus->mii_bus);
		mdiobus_free(bus->mii_bus);
		oct_mdio_writeq(0, bus->register_base + SMI_EN);
	}
	pci_set_drvdata(pdev, NULL);
}