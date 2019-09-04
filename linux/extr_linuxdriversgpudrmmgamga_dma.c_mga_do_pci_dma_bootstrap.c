#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int /*<<< orphan*/ * dma; scalar_t__ dev_private; } ;
struct drm_buf_desc {unsigned int count; int /*<<< orphan*/  size; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_5__ {scalar_t__ wagp_enable; scalar_t__ dma_access; TYPE_4__* primary; TYPE_4__* warp; } ;
typedef  TYPE_1__ drm_mga_private_t ;
struct TYPE_6__ {unsigned int primary_size; unsigned int secondary_bin_count; scalar_t__ agp_mode; int /*<<< orphan*/  secondary_bin_size; } ;
typedef  TYPE_2__ drm_mga_dma_bootstrap_t ;
struct TYPE_7__ {unsigned int size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,...) ; 
 int EFAULT ; 
 int ENOMEM ; 
 unsigned int MGA_WARP_UCODE_SIZE ; 
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  _DRM_CONSISTENT ; 
 int /*<<< orphan*/  _DRM_READ_ONLY ; 
 int drm_legacy_addbufs_pci (struct drm_device*,struct drm_buf_desc*) ; 
 int drm_legacy_addmap (struct drm_device*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_4__**) ; 
 int /*<<< orphan*/  memset (struct drm_buf_desc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mga_do_pci_dma_bootstrap(struct drm_device *dev,
				    drm_mga_dma_bootstrap_t *dma_bs)
{
	drm_mga_private_t *const dev_priv =
	    (drm_mga_private_t *) dev->dev_private;
	unsigned int warp_size = MGA_WARP_UCODE_SIZE;
	unsigned int primary_size;
	unsigned int bin_count;
	int err;
	struct drm_buf_desc req;

	if (dev->dma == NULL) {
		DRM_ERROR("dev->dma is NULL\n");
		return -EFAULT;
	}

	/* Make drm_legacy_addbufs happy by not trying to create a mapping for
	 * less than a page.
	 */
	if (warp_size < PAGE_SIZE)
		warp_size = PAGE_SIZE;

	/* The proper alignment is 0x100 for this mapping */
	err = drm_legacy_addmap(dev, 0, warp_size, _DRM_CONSISTENT,
				_DRM_READ_ONLY, &dev_priv->warp);
	if (err != 0) {
		DRM_ERROR("Unable to create mapping for WARP microcode: %d\n",
			  err);
		return err;
	}

	/* Other than the bottom two bits being used to encode other
	 * information, there don't appear to be any restrictions on the
	 * alignment of the primary or secondary DMA buffers.
	 */

	for (primary_size = dma_bs->primary_size; primary_size != 0;
	     primary_size >>= 1) {
		/* The proper alignment for this mapping is 0x04 */
		err = drm_legacy_addmap(dev, 0, primary_size, _DRM_CONSISTENT,
					_DRM_READ_ONLY, &dev_priv->primary);
		if (!err)
			break;
	}

	if (err != 0) {
		DRM_ERROR("Unable to allocate primary DMA region: %d\n", err);
		return -ENOMEM;
	}

	if (dev_priv->primary->size != dma_bs->primary_size) {
		DRM_INFO("Primary DMA buffer size reduced from %u to %u.\n",
			 dma_bs->primary_size,
			 (unsigned)dev_priv->primary->size);
		dma_bs->primary_size = dev_priv->primary->size;
	}

	for (bin_count = dma_bs->secondary_bin_count; bin_count > 0;
	     bin_count--) {
		(void)memset(&req, 0, sizeof(req));
		req.count = bin_count;
		req.size = dma_bs->secondary_bin_size;

		err = drm_legacy_addbufs_pci(dev, &req);
		if (!err)
			break;
	}

	if (bin_count == 0) {
		DRM_ERROR("Unable to add secondary DMA buffers: %d\n", err);
		return err;
	}

	if (bin_count != dma_bs->secondary_bin_count) {
		DRM_INFO("Secondary PCI DMA buffer bin count reduced from %u "
			 "to %u.\n", dma_bs->secondary_bin_count, bin_count);

		dma_bs->secondary_bin_count = bin_count;
	}

	dev_priv->dma_access = 0;
	dev_priv->wagp_enable = 0;

	dma_bs->agp_mode = 0;

	DRM_INFO("Initialized card for PCI DMA.\n");
	return 0;
}