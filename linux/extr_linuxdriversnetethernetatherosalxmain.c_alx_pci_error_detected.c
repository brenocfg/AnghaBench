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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
struct alx_priv {struct net_device* dev; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  alx_halt (struct alx_priv*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  netif_device_detach (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct alx_priv* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static pci_ers_result_t alx_pci_error_detected(struct pci_dev *pdev,
					       pci_channel_state_t state)
{
	struct alx_priv *alx = pci_get_drvdata(pdev);
	struct net_device *netdev = alx->dev;
	pci_ers_result_t rc = PCI_ERS_RESULT_NEED_RESET;

	dev_info(&pdev->dev, "pci error detected\n");

	rtnl_lock();

	if (netif_running(netdev)) {
		netif_device_detach(netdev);
		alx_halt(alx);
	}

	if (state == pci_channel_io_perm_failure)
		rc = PCI_ERS_RESULT_DISCONNECT;
	else
		pci_disable_device(pdev);

	rtnl_unlock();

	return rc;
}