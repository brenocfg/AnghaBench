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
typedef  int /*<<< orphan*/  uint32_t ;
struct mga_device {int num_crtc; int has_sdram; int* bpp_shifts; int /*<<< orphan*/  unique_rev_id; int /*<<< orphan*/ * rmmio; int /*<<< orphan*/  rmmio_size; int /*<<< orphan*/  rmmio_base; TYPE_1__* dev; int /*<<< orphan*/  type; } ;
struct drm_device {int /*<<< orphan*/  pdev; struct mga_device* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 scalar_t__ IS_G200_SE (struct mga_device*) ; 
 int /*<<< orphan*/  PCI_MGA_OPTION ; 
 int /*<<< orphan*/  RREG32 (int) ; 
 int /*<<< orphan*/  devm_request_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mga_vram_init (struct mga_device*) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_resource_start (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pcim_iomap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mgag200_device_init(struct drm_device *dev,
			       uint32_t flags)
{
	struct mga_device *mdev = dev->dev_private;
	int ret, option;

	mdev->type = flags;

	/* Hardcode the number of CRTCs to 1 */
	mdev->num_crtc = 1;

	pci_read_config_dword(dev->pdev, PCI_MGA_OPTION, &option);
	mdev->has_sdram = !(option & (1 << 14));

	/* BAR 0 is the framebuffer, BAR 1 contains registers */
	mdev->rmmio_base = pci_resource_start(mdev->dev->pdev, 1);
	mdev->rmmio_size = pci_resource_len(mdev->dev->pdev, 1);

	if (!devm_request_mem_region(mdev->dev->dev, mdev->rmmio_base, mdev->rmmio_size,
				"mgadrmfb_mmio")) {
		DRM_ERROR("can't reserve mmio registers\n");
		return -ENOMEM;
	}

	mdev->rmmio = pcim_iomap(dev->pdev, 1, 0);
	if (mdev->rmmio == NULL)
		return -ENOMEM;

	/* stash G200 SE model number for later use */
	if (IS_G200_SE(mdev))
		mdev->unique_rev_id = RREG32(0x1e24);

	ret = mga_vram_init(mdev);
	if (ret)
		return ret;

	mdev->bpp_shifts[0] = 0;
	mdev->bpp_shifts[1] = 1;
	mdev->bpp_shifts[2] = 0;
	mdev->bpp_shifts[3] = 2;
	return 0;
}