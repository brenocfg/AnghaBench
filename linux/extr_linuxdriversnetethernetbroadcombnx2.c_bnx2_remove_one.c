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
struct bnx2 {int flags; int /*<<< orphan*/  temp_stats_blk; int /*<<< orphan*/  regview; int /*<<< orphan*/  pdev; int /*<<< orphan*/  reset_task; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int BNX2_FLAG_AER_ENABLED ; 
 int /*<<< orphan*/  bnx2_free_stats_blk (struct net_device*) ; 
 int /*<<< orphan*/  bnx2_release_firmware (struct bnx2*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct bnx2* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void
bnx2_remove_one(struct pci_dev *pdev)
{
	struct net_device *dev = pci_get_drvdata(pdev);
	struct bnx2 *bp = netdev_priv(dev);

	unregister_netdev(dev);

	del_timer_sync(&bp->timer);
	cancel_work_sync(&bp->reset_task);

	pci_iounmap(bp->pdev, bp->regview);

	bnx2_free_stats_blk(dev);
	kfree(bp->temp_stats_blk);

	if (bp->flags & BNX2_FLAG_AER_ENABLED) {
		pci_disable_pcie_error_reporting(pdev);
		bp->flags &= ~BNX2_FLAG_AER_ENABLED;
	}

	bnx2_release_firmware(bp);

	free_netdev(dev);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
}