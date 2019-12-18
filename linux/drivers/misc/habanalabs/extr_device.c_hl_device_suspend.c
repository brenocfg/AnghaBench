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
struct hl_device {int disabled; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; TYPE_1__* asic_funcs; int /*<<< orphan*/  send_cpu_message_lock; int /*<<< orphan*/  in_reset; } ;
struct TYPE_2__ {int (* suspend ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_queues_unlock ) (struct hl_device*) ;int /*<<< orphan*/  (* hw_queues_lock ) (struct hl_device*) ;} ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  PCI_D3hot ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_save_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_power_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct hl_device*) ; 
 int /*<<< orphan*/  stub2 (struct hl_device*) ; 
 int stub3 (struct hl_device*) ; 

int hl_device_suspend(struct hl_device *hdev)
{
	int rc;

	pci_save_state(hdev->pdev);

	/* Block future CS/VM/JOB completion operations */
	rc = atomic_cmpxchg(&hdev->in_reset, 0, 1);
	if (rc) {
		dev_err(hdev->dev, "Can't suspend while in reset\n");
		return -EIO;
	}

	/* This blocks all other stuff that is not blocked by in_reset */
	hdev->disabled = true;

	/*
	 * Flush anyone that is inside the critical section of enqueue
	 * jobs to the H/W
	 */
	hdev->asic_funcs->hw_queues_lock(hdev);
	hdev->asic_funcs->hw_queues_unlock(hdev);

	/* Flush processes that are sending message to CPU */
	mutex_lock(&hdev->send_cpu_message_lock);
	mutex_unlock(&hdev->send_cpu_message_lock);

	rc = hdev->asic_funcs->suspend(hdev);
	if (rc)
		dev_err(hdev->dev,
			"Failed to disable PCI access of device CPU\n");

	/* Shut down the device */
	pci_disable_device(hdev->pdev);
	pci_set_power_state(hdev->pdev, PCI_D3hot);

	return 0;
}