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
struct nouveau_drm {int /*<<< orphan*/  vga_pm_domain; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  nouveau_is_optimus () ; 
 scalar_t__ nouveau_is_v1_dsm () ; 
 int nouveau_pmops_runtime () ; 
 int /*<<< orphan*/  nouveau_switcheroo_ops ; 
 int /*<<< orphan*/  nouveau_vga_set_decode ; 
 scalar_t__ pci_is_thunderbolt_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_client_register (int /*<<< orphan*/ ,struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_switcheroo_init_domain_pm_ops (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vga_switcheroo_register_client (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void
nouveau_vga_init(struct nouveau_drm *drm)
{
	struct drm_device *dev = drm->dev;
	bool runtime = nouveau_pmops_runtime();

	/* only relevant for PCI devices */
	if (!dev->pdev)
		return;

	vga_client_register(dev->pdev, dev, NULL, nouveau_vga_set_decode);

	/* don't register Thunderbolt eGPU with vga_switcheroo */
	if (pci_is_thunderbolt_attached(dev->pdev))
		return;

	vga_switcheroo_register_client(dev->pdev, &nouveau_switcheroo_ops, runtime);

	if (runtime && nouveau_is_v1_dsm() && !nouveau_is_optimus())
		vga_switcheroo_init_domain_pm_ops(drm->dev->dev, &drm->vga_pm_domain);
}