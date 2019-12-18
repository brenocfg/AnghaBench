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
struct tx_desc {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct dmfe_board_info {int /*<<< orphan*/  buf_pool_dma_ptr; int /*<<< orphan*/  buf_pool_ptr; int /*<<< orphan*/  pdev; int /*<<< orphan*/  desc_pool_dma_ptr; int /*<<< orphan*/  desc_pool_ptr; int /*<<< orphan*/  ioaddr; } ;

/* Variables and functions */
 int DESC_ALL_CNT ; 
 int /*<<< orphan*/  DMFE_DBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int TX_BUF_ALLOC ; 
 int TX_DESC_CNT ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 struct dmfe_board_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void dmfe_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct dmfe_board_info *db = netdev_priv(dev);

	DMFE_DBUG(0, "dmfe_remove_one()", 0);

 	if (dev) {

		unregister_netdev(dev);
		pci_iounmap(db->pdev, db->ioaddr);
		pci_free_consistent(db->pdev, sizeof(struct tx_desc) *
					DESC_ALL_CNT + 0x20, db->desc_pool_ptr,
 					db->desc_pool_dma_ptr);
		pci_free_consistent(db->pdev, TX_BUF_ALLOC * TX_DESC_CNT + 4,
					db->buf_pool_ptr, db->buf_pool_dma_ptr);
		pci_release_regions(pdev);
		free_netdev(dev);	/* free board information */
	}

	DMFE_DBUG(0, "dmfe_remove_one() exit", 0);
}