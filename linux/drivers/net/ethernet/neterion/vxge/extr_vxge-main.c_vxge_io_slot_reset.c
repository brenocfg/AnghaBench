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
struct vxgedev {int dummy; } ;
struct pci_dev {int dummy; } ;
struct net_device {int dummy; } ;
struct __vxge_hw_device {struct net_device* ndev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_RECOVERED ; 
 int /*<<< orphan*/  VXGE_LL_FULL_RESET ; 
 int /*<<< orphan*/  do_vxge_reset (struct vxgedev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct vxgedev* netdev_priv (struct net_device*) ; 
 scalar_t__ pci_enable_device (struct pci_dev*) ; 
 struct __vxge_hw_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t vxge_io_slot_reset(struct pci_dev *pdev)
{
	struct __vxge_hw_device *hldev = pci_get_drvdata(pdev);
	struct net_device *netdev = hldev->ndev;

	struct vxgedev *vdev = netdev_priv(netdev);

	if (pci_enable_device(pdev)) {
		netdev_err(netdev, "Cannot re-enable device after reset\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	pci_set_master(pdev);
	do_vxge_reset(vdev, VXGE_LL_FULL_RESET);

	return PCI_ERS_RESULT_RECOVERED;
}