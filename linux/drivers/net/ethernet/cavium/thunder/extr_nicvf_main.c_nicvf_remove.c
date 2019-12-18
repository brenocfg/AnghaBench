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
struct nicvf {int /*<<< orphan*/  ptp_clock; scalar_t__ drv_stats; int /*<<< orphan*/ * nicvf_rx_mode_wq; TYPE_1__* pnicvf; } ;
struct net_device {scalar_t__ reg_state; } ;
struct TYPE_2__ {struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ NETREG_REGISTERED ; 
 int /*<<< orphan*/  cavium_ptp_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (scalar_t__) ; 
 struct nicvf* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nicvf_unregister_interrupts (struct nicvf*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct net_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static void nicvf_remove(struct pci_dev *pdev)
{
	struct net_device *netdev = pci_get_drvdata(pdev);
	struct nicvf *nic;
	struct net_device *pnetdev;

	if (!netdev)
		return;

	nic = netdev_priv(netdev);
	pnetdev = nic->pnicvf->netdev;

	/* Check if this Qset is assigned to different VF.
	 * If yes, clean primary and all secondary Qsets.
	 */
	if (pnetdev && (pnetdev->reg_state == NETREG_REGISTERED))
		unregister_netdev(pnetdev);
	if (nic->nicvf_rx_mode_wq) {
		destroy_workqueue(nic->nicvf_rx_mode_wq);
		nic->nicvf_rx_mode_wq = NULL;
	}
	nicvf_unregister_interrupts(nic);
	pci_set_drvdata(pdev, NULL);
	if (nic->drv_stats)
		free_percpu(nic->drv_stats);
	cavium_ptp_put(nic->ptp_clock);
	free_netdev(netdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
}