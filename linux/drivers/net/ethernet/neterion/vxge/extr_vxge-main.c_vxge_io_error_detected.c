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
struct __vxge_hw_device {struct net_device* ndev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  do_vxge_close (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct __vxge_hw_device* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t vxge_io_error_detected(struct pci_dev *pdev,
						pci_channel_state_t state)
{
	struct __vxge_hw_device *hldev = pci_get_drvdata(pdev);
	struct net_device *netdev = hldev->ndev;

	netif_device_detach(netdev);

	if (state == pci_channel_io_perm_failure)
		return PCI_ERS_RESULT_DISCONNECT;

	if (netif_running(netdev)) {
		/* Bring down the card, while avoiding PCI I/O */
		do_vxge_close(netdev, 0);
	}

	pci_disable_device(pdev);

	return PCI_ERS_RESULT_NEED_RESET;
}