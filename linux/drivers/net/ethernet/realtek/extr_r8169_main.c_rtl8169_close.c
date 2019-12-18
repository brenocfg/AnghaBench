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
struct TYPE_2__ {int /*<<< orphan*/  work; int /*<<< orphan*/  flags; } ;
struct rtl8169_private {int /*<<< orphan*/ * RxDescArray; int /*<<< orphan*/ * TxDescArray; int /*<<< orphan*/  TxPhyAddr; int /*<<< orphan*/  RxPhyAddr; int /*<<< orphan*/  phydev; TYPE_1__ wk; struct pci_dev* pci_dev; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R8169_RX_RING_BYTES ; 
 int /*<<< orphan*/  R8169_TX_RING_BYTES ; 
 int /*<<< orphan*/  RTL_FLAG_MAX ; 
 int /*<<< orphan*/  bitmap_zero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_irq (struct pci_dev*,int /*<<< orphan*/ ,struct rtl8169_private*) ; 
 int /*<<< orphan*/  phy_disconnect (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtl8169_down (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_update_counters (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_lock_work (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_unlock_work (struct rtl8169_private*) ; 

__attribute__((used)) static int rtl8169_close(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);
	struct pci_dev *pdev = tp->pci_dev;

	pm_runtime_get_sync(&pdev->dev);

	/* Update counters before going down */
	rtl8169_update_counters(tp);

	rtl_lock_work(tp);
	/* Clear all task flags */
	bitmap_zero(tp->wk.flags, RTL_FLAG_MAX);

	rtl8169_down(dev);
	rtl_unlock_work(tp);

	cancel_work_sync(&tp->wk.work);

	phy_disconnect(tp->phydev);

	pci_free_irq(pdev, 0, tp);

	dma_free_coherent(&pdev->dev, R8169_RX_RING_BYTES, tp->RxDescArray,
			  tp->RxPhyAddr);
	dma_free_coherent(&pdev->dev, R8169_TX_RING_BYTES, tp->TxDescArray,
			  tp->TxPhyAddr);
	tp->TxDescArray = NULL;
	tp->RxDescArray = NULL;

	pm_runtime_put_sync(&pdev->dev);

	return 0;
}