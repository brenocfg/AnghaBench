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
struct net_device {int dummy; } ;
struct c_can_priv {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_c_can_dev (struct net_device*) ; 
 struct c_can_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_clear_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_c_can_dev (struct net_device*) ; 

__attribute__((used)) static void c_can_pci_remove(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct c_can_priv *priv = netdev_priv(dev);

	unregister_c_can_dev(dev);

	free_c_can_dev(dev);

	pci_iounmap(pdev, priv->base);
	pci_disable_msi(pdev);
	pci_clear_master(pdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}