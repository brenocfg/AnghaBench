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
struct vmw_private {scalar_t__ map_mode; struct drm_device* dev; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIT_MASK (int) ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int dma_set_mask_and_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vmw_dma_phys ; 
 scalar_t__ vmw_restrict_dma_mask ; 

__attribute__((used)) static int vmw_dma_masks(struct vmw_private *dev_priv)
{
	struct drm_device *dev = dev_priv->dev;
	int ret = 0;

	ret = dma_set_mask_and_coherent(dev->dev, DMA_BIT_MASK(64));
	if (dev_priv->map_mode != vmw_dma_phys &&
	    (sizeof(unsigned long) == 4 || vmw_restrict_dma_mask)) {
		DRM_INFO("Restricting DMA addresses to 44 bits.\n");
		return dma_set_mask_and_coherent(dev->dev, DMA_BIT_MASK(44));
	}

	return ret;
}