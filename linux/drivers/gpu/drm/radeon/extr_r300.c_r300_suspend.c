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
struct radeon_device {int flags; } ;

/* Variables and functions */
 int RADEON_IS_PCI ; 
 int RADEON_IS_PCIE ; 
 int /*<<< orphan*/  r100_cp_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_irq_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  r100_pci_gart_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_pm_suspend (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_wb_disable (struct radeon_device*) ; 
 int /*<<< orphan*/  rv370_pcie_gart_disable (struct radeon_device*) ; 

int r300_suspend(struct radeon_device *rdev)
{
	radeon_pm_suspend(rdev);
	r100_cp_disable(rdev);
	radeon_wb_disable(rdev);
	r100_irq_disable(rdev);
	if (rdev->flags & RADEON_IS_PCIE)
		rv370_pcie_gart_disable(rdev);
	if (rdev->flags & RADEON_IS_PCI)
		r100_pci_gart_disable(rdev);
	return 0;
}