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
struct drm_crtc {TYPE_2__* dev; } ;
struct dma_fence {int dummy; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {char const* name; } ;

/* Variables and functions */
 struct drm_crtc* fence_to_crtc (struct dma_fence*) ; 

__attribute__((used)) static const char *drm_crtc_fence_get_driver_name(struct dma_fence *fence)
{
	struct drm_crtc *crtc = fence_to_crtc(fence);

	return crtc->dev->driver->name;
}