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
struct ql3_adapter {int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  index; int /*<<< orphan*/  napi; int /*<<< orphan*/  adapter_timer; TYPE_1__* pdev; int /*<<< orphan*/  flags; struct net_device* ndev; scalar_t__ msi; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_ADAPTER_UP ; 
 int /*<<< orphan*/  QL_LINK_MASTER ; 
 int /*<<< orphan*/  QL_MSI_ENABLED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_1__*) ; 
 int ql_adapter_reset (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_disable_interrupts (struct ql3_adapter*) ; 
 int /*<<< orphan*/  ql_free_mem_resources (struct ql3_adapter*) ; 
 scalar_t__ ql_wait_for_drvr_lock (struct ql3_adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_adapter_down(struct ql3_adapter *qdev, int do_reset)
{
	struct net_device *ndev = qdev->ndev;
	int retval = 0;

	netif_stop_queue(ndev);
	netif_carrier_off(ndev);

	clear_bit(QL_ADAPTER_UP, &qdev->flags);
	clear_bit(QL_LINK_MASTER, &qdev->flags);

	ql_disable_interrupts(qdev);

	free_irq(qdev->pdev->irq, ndev);

	if (qdev->msi && test_bit(QL_MSI_ENABLED, &qdev->flags)) {
		netdev_info(qdev->ndev, "calling pci_disable_msi()\n");
		clear_bit(QL_MSI_ENABLED, &qdev->flags);
		pci_disable_msi(qdev->pdev);
	}

	del_timer_sync(&qdev->adapter_timer);

	napi_disable(&qdev->napi);

	if (do_reset) {
		int soft_reset;
		unsigned long hw_flags;

		spin_lock_irqsave(&qdev->hw_lock, hw_flags);
		if (ql_wait_for_drvr_lock(qdev)) {
			soft_reset = ql_adapter_reset(qdev);
			if (soft_reset) {
				netdev_err(ndev, "ql_adapter_reset(%d) FAILED!\n",
					   qdev->index);
			}
			netdev_err(ndev,
				   "Releasing driver lock via chip reset\n");
		} else {
			netdev_err(ndev,
				   "Could not acquire driver lock to do reset!\n");
			retval = -1;
		}
		spin_unlock_irqrestore(&qdev->hw_lock, hw_flags);
	}
	ql_free_mem_resources(qdev);
	return retval;
}