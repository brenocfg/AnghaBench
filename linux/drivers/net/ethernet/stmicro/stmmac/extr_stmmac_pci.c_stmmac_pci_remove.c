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
struct stmmac_priv {TYPE_1__* plat; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ stmmac_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int PCI_STD_RESOURCE_END ; 
 int /*<<< orphan*/  clk_unregister_fixed_rate (scalar_t__) ; 
 struct net_device* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 struct stmmac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 scalar_t__ pci_resource_len (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pcim_iounmap_regions (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stmmac_dvr_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stmmac_pci_remove(struct pci_dev *pdev)
{
	struct net_device *ndev = dev_get_drvdata(&pdev->dev);
	struct stmmac_priv *priv = netdev_priv(ndev);
	int i;

	stmmac_dvr_remove(&pdev->dev);

	if (priv->plat->stmmac_clk)
		clk_unregister_fixed_rate(priv->plat->stmmac_clk);

	for (i = 0; i <= PCI_STD_RESOURCE_END; i++) {
		if (pci_resource_len(pdev, i) == 0)
			continue;
		pcim_iounmap_regions(pdev, BIT(i));
		break;
	}

	pci_disable_device(pdev);
}