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
struct hibmc_drm_private {int /*<<< orphan*/  fb_size; struct drm_device* dev; } ;
struct drm_vram_mm {int dummy; } ;
struct drm_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ IS_ERR (struct drm_vram_mm*) ; 
 int PTR_ERR (struct drm_vram_mm*) ; 
 int /*<<< orphan*/  drm_gem_vram_mm_funcs ; 
 struct drm_vram_mm* drm_vram_helper_alloc_mm (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int hibmc_mm_init(struct hibmc_drm_private *hibmc)
{
	struct drm_vram_mm *vmm;
	int ret;
	struct drm_device *dev = hibmc->dev;

	vmm = drm_vram_helper_alloc_mm(dev,
				       pci_resource_start(dev->pdev, 0),
				       hibmc->fb_size, &drm_gem_vram_mm_funcs);
	if (IS_ERR(vmm)) {
		ret = PTR_ERR(vmm);
		DRM_ERROR("Error initializing VRAM MM; %d\n", ret);
		return ret;
	}

	return 0;
}