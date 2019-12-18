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
struct hl_device {int disabled; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; int /*<<< orphan*/  in_reset; TYPE_1__* asic_funcs; } ;
struct TYPE_2__ {int (* resume ) (struct hl_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int hl_device_reset (struct hl_device*,int,int) ; 
 int /*<<< orphan*/  pci_clear_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int pci_enable_device_mem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_restore_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_master (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct hl_device*) ; 

int hl_device_resume(struct hl_device *hdev)
{
	int rc;

	pci_set_power_state(hdev->pdev, PCI_D0);
	pci_restore_state(hdev->pdev);
	rc = pci_enable_device_mem(hdev->pdev);
	if (rc) {
		dev_err(hdev->dev,
			"Failed to enable PCI device in resume\n");
		return rc;
	}

	pci_set_master(hdev->pdev);

	rc = hdev->asic_funcs->resume(hdev);
	if (rc) {
		dev_err(hdev->dev, "Failed to resume device after suspend\n");
		goto disable_device;
	}


	hdev->disabled = false;
	atomic_set(&hdev->in_reset, 0);

	rc = hl_device_reset(hdev, true, false);
	if (rc) {
		dev_err(hdev->dev, "Failed to reset device during resume\n");
		goto disable_device;
	}

	return 0;

disable_device:
	pci_clear_master(hdev->pdev);
	pci_disable_device(hdev->pdev);

	return rc;
}