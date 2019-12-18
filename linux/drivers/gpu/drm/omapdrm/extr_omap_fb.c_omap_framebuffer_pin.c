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
struct plane {scalar_t__ dma_addr; } ;
struct omap_framebuffer {scalar_t__ pin_count; int /*<<< orphan*/  lock; struct plane* planes; } ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; TYPE_1__* format; } ;
struct TYPE_2__ {int num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  omap_gem_dma_sync_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int omap_gem_pin (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  omap_gem_unpin (int /*<<< orphan*/ ) ; 
 struct omap_framebuffer* to_omap_framebuffer (struct drm_framebuffer*) ; 

int omap_framebuffer_pin(struct drm_framebuffer *fb)
{
	struct omap_framebuffer *omap_fb = to_omap_framebuffer(fb);
	int ret, i, n = fb->format->num_planes;

	mutex_lock(&omap_fb->lock);

	if (omap_fb->pin_count > 0) {
		omap_fb->pin_count++;
		mutex_unlock(&omap_fb->lock);
		return 0;
	}

	for (i = 0; i < n; i++) {
		struct plane *plane = &omap_fb->planes[i];
		ret = omap_gem_pin(fb->obj[i], &plane->dma_addr);
		if (ret)
			goto fail;
		omap_gem_dma_sync_buffer(fb->obj[i], DMA_TO_DEVICE);
	}

	omap_fb->pin_count++;

	mutex_unlock(&omap_fb->lock);

	return 0;

fail:
	for (i--; i >= 0; i--) {
		struct plane *plane = &omap_fb->planes[i];
		omap_gem_unpin(fb->obj[i]);
		plane->dma_addr = 0;
	}

	mutex_unlock(&omap_fb->lock);

	return ret;
}