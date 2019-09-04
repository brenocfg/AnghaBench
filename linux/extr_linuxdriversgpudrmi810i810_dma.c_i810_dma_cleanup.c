#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct drm_device_dma {int buf_count; struct drm_buf** buflist; } ;
struct drm_device {int /*<<< orphan*/ * dev_private; int /*<<< orphan*/  pdev; scalar_t__ irq_enabled; struct drm_device_dma* dma; } ;
struct drm_buf {scalar_t__ total; TYPE_3__* dev_private; } ;
struct TYPE_4__ {int /*<<< orphan*/  map; scalar_t__ virtual_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  dma_status_page; scalar_t__ hw_status_page; TYPE_1__ ring; } ;
typedef  TYPE_2__ drm_i810_private_t ;
struct TYPE_6__ {int /*<<< orphan*/  map; scalar_t__ kernel_virtual; } ;
typedef  TYPE_3__ drm_i810_buf_priv_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_HAVE_IRQ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_irq_uninstall (struct drm_device*) ; 
 int /*<<< orphan*/  drm_legacy_ioremapfree (int /*<<< orphan*/ *,struct drm_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i810_dma_cleanup(struct drm_device *dev)
{
	struct drm_device_dma *dma = dev->dma;

	/* Make sure interrupts are disabled here because the uninstall ioctl
	 * may not have been called from userspace and after dev_private
	 * is freed, it's too late.
	 */
	if (drm_core_check_feature(dev, DRIVER_HAVE_IRQ) && dev->irq_enabled)
		drm_irq_uninstall(dev);

	if (dev->dev_private) {
		int i;
		drm_i810_private_t *dev_priv =
		    (drm_i810_private_t *) dev->dev_private;

		if (dev_priv->ring.virtual_start)
			drm_legacy_ioremapfree(&dev_priv->ring.map, dev);
		if (dev_priv->hw_status_page) {
			pci_free_consistent(dev->pdev, PAGE_SIZE,
					    dev_priv->hw_status_page,
					    dev_priv->dma_status_page);
		}
		kfree(dev->dev_private);
		dev->dev_private = NULL;

		for (i = 0; i < dma->buf_count; i++) {
			struct drm_buf *buf = dma->buflist[i];
			drm_i810_buf_priv_t *buf_priv = buf->dev_private;

			if (buf_priv->kernel_virtual && buf->total)
				drm_legacy_ioremapfree(&buf_priv->map, dev);
		}
	}
	return 0;
}