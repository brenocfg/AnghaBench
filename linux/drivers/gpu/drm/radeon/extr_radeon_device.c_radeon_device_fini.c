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
struct radeon_device {int shutdown; int flags; scalar_t__ family; int /*<<< orphan*/ * rmmio; int /*<<< orphan*/ * rio_mem; int /*<<< orphan*/  pdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_BONAIRE ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int RADEON_IS_PX ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_is_thunderbolt_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_bo_evict_vram (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_doorbell_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  radeon_fini (struct radeon_device*) ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_fini_domain_pm_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (int /*<<< orphan*/ ) ; 

void radeon_device_fini(struct radeon_device *rdev)
{
	DRM_INFO("radeon: finishing device.\n");
	rdev->shutdown = true;
	/* evict vram memory */
	radeon_bo_evict_vram(rdev);
	radeon_fini(rdev);
	if (!pci_is_thunderbolt_attached(rdev->pdev))
		vga_switcheroo_unregister_client(rdev->pdev);
	if (rdev->flags & RADEON_IS_PX)
		vga_switcheroo_fini_domain_pm_ops(rdev->dev);
	vga_client_register(rdev->pdev, NULL, NULL, NULL);
	if (rdev->rio_mem)
		pci_iounmap(rdev->pdev, rdev->rio_mem);
	rdev->rio_mem = NULL;
	iounmap(rdev->rmmio);
	rdev->rmmio = NULL;
	if (rdev->family >= CHIP_BONAIRE)
		radeon_doorbell_fini(rdev);
}