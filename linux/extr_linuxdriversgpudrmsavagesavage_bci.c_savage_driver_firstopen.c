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
struct drm_device {int /*<<< orphan*/  pdev; TYPE_1__* dev_private; } ;
struct TYPE_2__ {scalar_t__ chipset; int /*<<< orphan*/  aperture; int /*<<< orphan*/  fb; int /*<<< orphan*/  mmio; void** mtrr_handles; } ;
typedef  TYPE_1__ drm_savage_private_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned long long) ; 
 scalar_t__ S3_SAVAGE2000 ; 
 scalar_t__ S3_SAVAGE3D_SERIES (scalar_t__) ; 
 scalar_t__ S3_SUPERSAVAGE ; 
 unsigned long SAVAGE_APERTURE_OFFSET ; 
 unsigned long SAVAGE_APERTURE_SIZE ; 
 unsigned long SAVAGE_FB_SIZE_S3 ; 
 unsigned long SAVAGE_FB_SIZE_S4 ; 
 unsigned long SAVAGE_MMIO_SIZE ; 
 int /*<<< orphan*/  _DRM_FRAME_BUFFER ; 
 int /*<<< orphan*/  _DRM_READ_ONLY ; 
 int /*<<< orphan*/  _DRM_REGISTERS ; 
 int /*<<< orphan*/  _DRM_WRITE_COMBINING ; 
 void* arch_phys_wc_add (unsigned long,int) ; 
 int drm_legacy_addmap (struct drm_device*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int pci_resource_len (int /*<<< orphan*/ ,int) ; 
 unsigned long pci_resource_start (int /*<<< orphan*/ ,int) ; 

int savage_driver_firstopen(struct drm_device *dev)
{
	drm_savage_private_t *dev_priv = dev->dev_private;
	unsigned long mmio_base, fb_base, fb_size, aperture_base;
	/* fb_rsrc and aper_rsrc aren't really used currently, but still exist
	 * in case we decide we need information on the BAR for BSD in the
	 * future.
	 */
	unsigned int fb_rsrc, aper_rsrc;
	int ret = 0;

	if (S3_SAVAGE3D_SERIES(dev_priv->chipset)) {
		fb_rsrc = 0;
		fb_base = pci_resource_start(dev->pdev, 0);
		fb_size = SAVAGE_FB_SIZE_S3;
		mmio_base = fb_base + SAVAGE_FB_SIZE_S3;
		aper_rsrc = 0;
		aperture_base = fb_base + SAVAGE_APERTURE_OFFSET;
		/* this should always be true */
		if (pci_resource_len(dev->pdev, 0) == 0x08000000) {
			/* Don't make MMIO write-cobining! We need 3
			 * MTRRs. */
			dev_priv->mtrr_handles[0] =
				arch_phys_wc_add(fb_base, 0x01000000);
			dev_priv->mtrr_handles[1] =
				arch_phys_wc_add(fb_base + 0x02000000,
						 0x02000000);
			dev_priv->mtrr_handles[2] =
				arch_phys_wc_add(fb_base + 0x04000000,
						0x04000000);
		} else {
			DRM_ERROR("strange pci_resource_len %08llx\n",
				  (unsigned long long)
				  pci_resource_len(dev->pdev, 0));
		}
	} else if (dev_priv->chipset != S3_SUPERSAVAGE &&
		   dev_priv->chipset != S3_SAVAGE2000) {
		mmio_base = pci_resource_start(dev->pdev, 0);
		fb_rsrc = 1;
		fb_base = pci_resource_start(dev->pdev, 1);
		fb_size = SAVAGE_FB_SIZE_S4;
		aper_rsrc = 1;
		aperture_base = fb_base + SAVAGE_APERTURE_OFFSET;
		/* this should always be true */
		if (pci_resource_len(dev->pdev, 1) == 0x08000000) {
			/* Can use one MTRR to cover both fb and
			 * aperture. */
			dev_priv->mtrr_handles[0] =
				arch_phys_wc_add(fb_base,
						 0x08000000);
		} else {
			DRM_ERROR("strange pci_resource_len %08llx\n",
				  (unsigned long long)
				  pci_resource_len(dev->pdev, 1));
		}
	} else {
		mmio_base = pci_resource_start(dev->pdev, 0);
		fb_rsrc = 1;
		fb_base = pci_resource_start(dev->pdev, 1);
		fb_size = pci_resource_len(dev->pdev, 1);
		aper_rsrc = 2;
		aperture_base = pci_resource_start(dev->pdev, 2);
		/* Automatic MTRR setup will do the right thing. */
	}

	ret = drm_legacy_addmap(dev, mmio_base, SAVAGE_MMIO_SIZE,
				_DRM_REGISTERS, _DRM_READ_ONLY,
				&dev_priv->mmio);
	if (ret)
		return ret;

	ret = drm_legacy_addmap(dev, fb_base, fb_size, _DRM_FRAME_BUFFER,
				_DRM_WRITE_COMBINING, &dev_priv->fb);
	if (ret)
		return ret;

	ret = drm_legacy_addmap(dev, aperture_base, SAVAGE_APERTURE_SIZE,
				_DRM_FRAME_BUFFER, _DRM_WRITE_COMBINING,
				&dev_priv->aperture);
	return ret;
}