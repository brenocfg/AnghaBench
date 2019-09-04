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
struct drm_device {TYPE_1__* dma; int /*<<< orphan*/  buf_alloc; scalar_t__ buf_use; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_HAVE_DMA ; 
 int /*<<< orphan*/  DRIVER_LEGACY ; 
 int DRM_MAX_ORDER ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_core_check_feature (struct drm_device*,int /*<<< orphan*/ ) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int drm_legacy_dma_setup(struct drm_device *dev)
{
	int i;

	if (!drm_core_check_feature(dev, DRIVER_HAVE_DMA) ||
	    !drm_core_check_feature(dev, DRIVER_LEGACY))
		return 0;

	dev->buf_use = 0;
	atomic_set(&dev->buf_alloc, 0);

	dev->dma = kzalloc(sizeof(*dev->dma), GFP_KERNEL);
	if (!dev->dma)
		return -ENOMEM;

	for (i = 0; i <= DRM_MAX_ORDER; i++)
		memset(&dev->dma->bufs[i], 0, sizeof(dev->dma->bufs[0]));

	return 0;
}