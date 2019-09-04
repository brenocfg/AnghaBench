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
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  enum pci_channel_state { ____Placeholder_pci_channel_state } pci_channel_state ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ioat_shutdown (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t ioat_pcie_error_detected(struct pci_dev *pdev,
						 enum pci_channel_state error)
{
	dev_dbg(&pdev->dev, "%s: PCIe AER error %d\n", DRV_NAME, error);

	/* quiesce and block I/O */
	ioat_shutdown(pdev);

	return PCI_ERS_RESULT_NEED_RESET;
}