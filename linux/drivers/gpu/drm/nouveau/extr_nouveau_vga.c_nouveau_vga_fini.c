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
struct nouveau_drm {struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_is_optimus () ; 
 scalar_t__ nouveau_is_v1_dsm () ; 
 int nouveau_pmops_runtime () ; 
 scalar_t__ pci_is_thunderbolt_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_fini_domain_pm_ops (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_switcheroo_unregister_client (int /*<<< orphan*/ ) ; 

void
nouveau_vga_fini(struct nouveau_drm *drm)
{
	struct drm_device *dev = drm->dev;
	bool runtime = nouveau_pmops_runtime();

	/* only relevant for PCI devices */
	if (!dev->pdev)
		return;

	vga_client_register(dev->pdev, NULL, NULL, NULL);

	if (pci_is_thunderbolt_attached(dev->pdev))
		return;

	vga_switcheroo_unregister_client(dev->pdev);
	if (runtime && nouveau_is_v1_dsm() && !nouveau_is_optimus())
		vga_switcheroo_fini_domain_pm_ops(drm->dev->dev);
}