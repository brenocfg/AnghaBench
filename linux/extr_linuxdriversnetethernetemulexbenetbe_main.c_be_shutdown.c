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
struct be_adapter {int /*<<< orphan*/  netdev; int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int /*<<< orphan*/  be_cancel_err_detection (struct be_adapter*) ; 
 int /*<<< orphan*/  be_cmd_reset_function (struct be_adapter*) ; 
 int /*<<< orphan*/  be_roce_dev_shutdown (struct be_adapter*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_device_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct be_adapter* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void be_shutdown(struct pci_dev *pdev)
{
	struct be_adapter *adapter = pci_get_drvdata(pdev);

	if (!adapter)
		return;

	be_roce_dev_shutdown(adapter);
	cancel_delayed_work_sync(&adapter->work);
	be_cancel_err_detection(adapter);

	netif_device_detach(adapter->netdev);

	be_cmd_reset_function(adapter);

	pci_disable_device(pdev);
}