#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct drm_device {scalar_t__ dev_private; scalar_t__ agp; } ;
struct TYPE_6__ {int used_new_dma_init; int /*<<< orphan*/  status; int /*<<< orphan*/  mmio; int /*<<< orphan*/  mmio_size; int /*<<< orphan*/  mmio_base; } ;
typedef  TYPE_1__ drm_mga_private_t ;
struct TYPE_7__ {scalar_t__ agp_mode; } ;
typedef  TYPE_2__ drm_mga_dma_bootstrap_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  MINIMAL_CLEANUP ; 
 int /*<<< orphan*/  SAREA_MAX ; 
 int _DRM_KERNEL ; 
 int _DRM_LOCKED ; 
 int _DRM_READ_ONLY ; 
 int /*<<< orphan*/  _DRM_REGISTERS ; 
 int /*<<< orphan*/  _DRM_SHM ; 
 int drm_legacy_addmap (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int mga_do_agp_dma_bootstrap (struct drm_device*,TYPE_2__*) ; 
 int /*<<< orphan*/  mga_do_cleanup_dma (struct drm_device*,int /*<<< orphan*/ ) ; 
 int mga_do_pci_dma_bootstrap (struct drm_device*,TYPE_2__*) ; 

__attribute__((used)) static int mga_do_dma_bootstrap(struct drm_device *dev,
				drm_mga_dma_bootstrap_t *dma_bs)
{
	const int is_agp = (dma_bs->agp_mode != 0) && dev->agp;
	int err;
	drm_mga_private_t *const dev_priv =
	    (drm_mga_private_t *) dev->dev_private;

	dev_priv->used_new_dma_init = 1;

	/* The first steps are the same for both PCI and AGP based DMA.  Map
	 * the cards MMIO registers and map a status page.
	 */
	err = drm_legacy_addmap(dev, dev_priv->mmio_base, dev_priv->mmio_size,
				_DRM_REGISTERS, _DRM_READ_ONLY,
				&dev_priv->mmio);
	if (err) {
		DRM_ERROR("Unable to map MMIO region: %d\n", err);
		return err;
	}

	err = drm_legacy_addmap(dev, 0, SAREA_MAX, _DRM_SHM,
				_DRM_READ_ONLY | _DRM_LOCKED | _DRM_KERNEL,
			 &dev_priv->status);
	if (err) {
		DRM_ERROR("Unable to map status region: %d\n", err);
		return err;
	}

	/* The DMA initialization procedure is slightly different for PCI and
	 * AGP cards.  AGP cards just allocate a large block of AGP memory and
	 * carve off portions of it for internal uses.  The remaining memory
	 * is returned to user-mode to be used for AGP textures.
	 */
	if (is_agp)
		err = mga_do_agp_dma_bootstrap(dev, dma_bs);

	/* If we attempted to initialize the card for AGP DMA but failed,
	 * clean-up any mess that may have been created.
	 */

	if (err)
		mga_do_cleanup_dma(dev, MINIMAL_CLEANUP);

	/* Not only do we want to try and initialized PCI cards for PCI DMA,
	 * but we also try to initialized AGP cards that could not be
	 * initialized for AGP DMA.  This covers the case where we have an AGP
	 * card in a system with an unsupported AGP chipset.  In that case the
	 * card will be detected as AGP, but we won't be able to allocate any
	 * AGP memory, etc.
	 */

	if (!is_agp || err)
		err = mga_do_pci_dma_bootstrap(dev, dma_bs);

	return err;
}