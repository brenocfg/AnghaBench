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
struct TYPE_2__ {int /*<<< orphan*/  vram_size; } ;
struct mga_device {int /*<<< orphan*/  fb_mtrr; TYPE_1__ mc; struct drm_device* dev; } ;
struct drm_vram_mm {int dummy; } ;
struct drm_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 scalar_t__ IS_ERR (struct drm_vram_mm*) ; 
 int PTR_ERR (struct drm_vram_mm*) ; 
 int /*<<< orphan*/  arch_io_reserve_memtype_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_mm_funcs ; 
 struct drm_vram_mm* drm_vram_helper_alloc_mm (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mgag200_mm_init(struct mga_device *mdev)
{
	struct drm_vram_mm *vmm;
	int ret;
	struct drm_device *dev = mdev->dev;

	vmm = drm_vram_helper_alloc_mm(dev, pci_resource_start(dev->pdev, 0),
				       mdev->mc.vram_size,
				       &drm_gem_vram_mm_funcs);
	if (IS_ERR(vmm)) {
		ret = PTR_ERR(vmm);
		DRM_ERROR("Error initializing VRAM MM; %d\n", ret);
		return ret;
	}

	arch_io_reserve_memtype_wc(pci_resource_start(dev->pdev, 0),
				   pci_resource_len(dev->pdev, 0));

	mdev->fb_mtrr = arch_phys_wc_add(pci_resource_start(dev->pdev, 0),
					 pci_resource_len(dev->pdev, 0));

	return 0;
}