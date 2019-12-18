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
struct TYPE_2__ {int /*<<< orphan*/  pdev; } ;
struct vbox_private {TYPE_1__ ddev; int /*<<< orphan*/  fb_mtrr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MTRR_WC ; 
 int /*<<< orphan*/  arch_phys_wc_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mtrr_del (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_vram_helper_release_mm (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vbox_mm_fini(struct vbox_private *vbox)
{
#ifdef DRM_MTRR_WC
	drm_mtrr_del(vbox->fb_mtrr,
		     pci_resource_start(vbox->ddev.pdev, 0),
		     pci_resource_len(vbox->ddev.pdev, 0), DRM_MTRR_WC);
#else
	arch_phys_wc_del(vbox->fb_mtrr);
#endif
	drm_vram_helper_release_mm(&vbox->ddev);
}