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
struct drm_device {int /*<<< orphan*/  pdev; } ;
struct vbox_private {int /*<<< orphan*/  fb_mtrr; int /*<<< orphan*/  available_vram_size; struct drm_device ddev; } ;
struct drm_vram_mm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_MTRR_WC ; 
 scalar_t__ IS_ERR (struct drm_vram_mm*) ; 
 int PTR_ERR (struct drm_vram_mm*) ; 
 int /*<<< orphan*/  arch_phys_wc_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_mm_funcs ; 
 int /*<<< orphan*/  drm_mtrr_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_vram_mm* drm_vram_helper_alloc_mm (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int vbox_mm_init(struct vbox_private *vbox)
{
	struct drm_vram_mm *vmm;
	int ret;
	struct drm_device *dev = &vbox->ddev;

	vmm = drm_vram_helper_alloc_mm(dev, pci_resource_start(dev->pdev, 0),
				       vbox->available_vram_size,
				       &drm_gem_vram_mm_funcs);
	if (IS_ERR(vmm)) {
		ret = PTR_ERR(vmm);
		DRM_ERROR("Error initializing VRAM MM; %d\n", ret);
		return ret;
	}

#ifdef DRM_MTRR_WC
	vbox->fb_mtrr = drm_mtrr_add(pci_resource_start(dev->pdev, 0),
				     pci_resource_len(dev->pdev, 0),
				     DRM_MTRR_WC);
#else
	vbox->fb_mtrr = arch_phys_wc_add(pci_resource_start(dev->pdev, 0),
					 pci_resource_len(dev->pdev, 0));
#endif
	return 0;
}