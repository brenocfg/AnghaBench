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
struct xircom_private {int /*<<< orphan*/  rx_dma_handle; int /*<<< orphan*/  rx_buffer; int /*<<< orphan*/  tx_dma_handle; int /*<<< orphan*/  tx_buffer; int /*<<< orphan*/  ioaddr; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct xircom_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void xircom_remove(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct xircom_private *card = netdev_priv(dev);
	struct device *d = &pdev->dev;

	unregister_netdev(dev);
	pci_iounmap(pdev, card->ioaddr);
	dma_free_coherent(d, 8192, card->tx_buffer, card->tx_dma_handle);
	dma_free_coherent(d, 8192, card->rx_buffer, card->rx_dma_handle);
	free_netdev(dev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}