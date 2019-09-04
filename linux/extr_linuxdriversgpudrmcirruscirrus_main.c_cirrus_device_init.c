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
typedef  int /*<<< orphan*/  uint32_t ;
struct pci_dev {int dummy; } ;
struct drm_device {int /*<<< orphan*/  pdev; } ;
struct cirrus_device {int num_crtc; int /*<<< orphan*/  rmmio_size; int /*<<< orphan*/  rmmio_base; int /*<<< orphan*/ * rmmio; struct drm_device* dev; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int cirrus_vram_init (struct cirrus_device*) ; 
 int /*<<< orphan*/ * ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int cirrus_device_init(struct cirrus_device *cdev,
		       struct drm_device *ddev,
		       struct pci_dev *pdev, uint32_t flags)
{
	int ret;

	cdev->dev = ddev;
	cdev->flags = flags;

	/* Hardcode the number of CRTCs to 1 */
	cdev->num_crtc = 1;

	/* BAR 0 is the framebuffer, BAR 1 contains registers */
	cdev->rmmio_base = pci_resource_start(cdev->dev->pdev, 1);
	cdev->rmmio_size = pci_resource_len(cdev->dev->pdev, 1);

	if (!request_mem_region(cdev->rmmio_base, cdev->rmmio_size,
				"cirrusdrmfb_mmio")) {
		DRM_ERROR("can't reserve mmio registers\n");
		return -ENOMEM;
	}

	cdev->rmmio = ioremap(cdev->rmmio_base, cdev->rmmio_size);

	if (cdev->rmmio == NULL)
		return -ENOMEM;

	ret = cirrus_vram_init(cdev);
	if (ret) {
		release_mem_region(cdev->rmmio_base, cdev->rmmio_size);
		return ret;
	}

	return 0;
}