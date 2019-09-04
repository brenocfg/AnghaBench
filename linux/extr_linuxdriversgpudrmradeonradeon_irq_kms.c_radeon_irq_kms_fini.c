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
struct TYPE_2__ {int installed; } ;
struct radeon_device {int /*<<< orphan*/  hotplug_work; int /*<<< orphan*/  pdev; scalar_t__ msi_enabled; TYPE_1__ irq; int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_irq_uninstall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msi (int /*<<< orphan*/ ) ; 

void radeon_irq_kms_fini(struct radeon_device *rdev)
{
	if (rdev->irq.installed) {
		drm_irq_uninstall(rdev->ddev);
		rdev->irq.installed = false;
		if (rdev->msi_enabled)
			pci_disable_msi(rdev->pdev);
		flush_delayed_work(&rdev->hotplug_work);
	}
}