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
struct pci_dev {int dummy; } ;
struct pch_can_priv {int /*<<< orphan*/  ndev; int /*<<< orphan*/  regs; int /*<<< orphan*/  dev; scalar_t__ use_msi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_candev (int /*<<< orphan*/ ) ; 
 struct pch_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pch_can_reset (struct pch_can_priv*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_candev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_can_remove(struct pci_dev *pdev)
{
	struct net_device *ndev = pci_get_drvdata(pdev);
	struct pch_can_priv *priv = netdev_priv(ndev);

	unregister_candev(priv->ndev);
	if (priv->use_msi)
		pci_disable_msi(priv->dev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pch_can_reset(priv);
	pci_iounmap(pdev, priv->regs);
	free_candev(priv->ndev);
}