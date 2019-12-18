#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {TYPE_2__* agp_buffer_map; TYPE_1__* dev_private; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ handle; } ;
struct TYPE_3__ {scalar_t__ dma_type; scalar_t__ dma_pages; TYPE_2__* cmd_dma; TYPE_2__ fake_dma; } ;
typedef  TYPE_1__ drm_savage_private_t ;

/* Variables and functions */
 scalar_t__ SAVAGE_DMA_AGP ; 
 scalar_t__ _DRM_AGP ; 
 int /*<<< orphan*/  drm_legacy_ioremapfree (TYPE_2__*,struct drm_device*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 

__attribute__((used)) static int savage_do_cleanup_bci(struct drm_device * dev)
{
	drm_savage_private_t *dev_priv = dev->dev_private;

	if (dev_priv->cmd_dma == &dev_priv->fake_dma) {
		kfree(dev_priv->fake_dma.handle);
	} else if (dev_priv->cmd_dma && dev_priv->cmd_dma->handle &&
		   dev_priv->cmd_dma->type == _DRM_AGP &&
		   dev_priv->dma_type == SAVAGE_DMA_AGP)
		drm_legacy_ioremapfree(dev_priv->cmd_dma, dev);

	if (dev_priv->dma_type == SAVAGE_DMA_AGP &&
	    dev->agp_buffer_map && dev->agp_buffer_map->handle) {
		drm_legacy_ioremapfree(dev->agp_buffer_map, dev);
		/* make sure the next instance (which may be running
		 * in PCI mode) doesn't try to use an old
		 * agp_buffer_map. */
		dev->agp_buffer_map = NULL;
	}

	kfree(dev_priv->dma_pages);

	return 0;
}