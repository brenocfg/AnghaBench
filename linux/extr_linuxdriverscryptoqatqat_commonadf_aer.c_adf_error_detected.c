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
struct adf_accel_dev {int dummy; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  scalar_t__ pci_channel_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_NEED_RESET ; 
 struct adf_accel_dev* adf_devmgr_pci_to_accel_dev (struct pci_dev*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ pci_channel_io_perm_failure ; 

__attribute__((used)) static pci_ers_result_t adf_error_detected(struct pci_dev *pdev,
					   pci_channel_state_t state)
{
	struct adf_accel_dev *accel_dev = adf_devmgr_pci_to_accel_dev(pdev);

	dev_info(&pdev->dev, "Acceleration driver hardware error detected.\n");
	if (!accel_dev) {
		dev_err(&pdev->dev, "Can't find acceleration device\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	if (state == pci_channel_io_perm_failure) {
		dev_err(&pdev->dev, "Can't recover from device error\n");
		return PCI_ERS_RESULT_DISCONNECT;
	}

	return PCI_ERS_RESULT_NEED_RESET;
}