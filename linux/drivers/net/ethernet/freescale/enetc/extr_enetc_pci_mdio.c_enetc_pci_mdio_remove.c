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
struct pci_dev {int dummy; } ;
struct mii_bus {struct enetc_mdio_priv* priv; } ;
struct enetc_mdio_priv {TYPE_1__* hw; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct mii_bus* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_mem_regions (struct pci_dev*) ; 

__attribute__((used)) static void enetc_pci_mdio_remove(struct pci_dev *pdev)
{
	struct mii_bus *bus = pci_get_drvdata(pdev);
	struct enetc_mdio_priv *mdio_priv;

	mdiobus_unregister(bus);
	mdio_priv = bus->priv;
	iounmap(mdio_priv->hw->port);
	pci_release_mem_regions(pdev);
	pci_disable_device(pdev);
}