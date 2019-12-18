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
struct drm_vblank_crtc {unsigned int pipe; int /*<<< orphan*/  seqlock; int /*<<< orphan*/  disable_timer; int /*<<< orphan*/  queue; struct drm_device* dev; } ;
struct drm_device {unsigned int num_crtcs; int vblank_disable_immediate; TYPE_1__* driver; struct drm_vblank_crtc* vblank; int /*<<< orphan*/  vblank_time_lock; int /*<<< orphan*/  vbl_lock; } ;
struct TYPE_2__ {scalar_t__ get_vblank_timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct drm_vblank_crtc* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seqlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vblank_disable_fn ; 

int drm_vblank_init(struct drm_device *dev, unsigned int num_crtcs)
{
	int ret = -ENOMEM;
	unsigned int i;

	spin_lock_init(&dev->vbl_lock);
	spin_lock_init(&dev->vblank_time_lock);

	dev->num_crtcs = num_crtcs;

	dev->vblank = kcalloc(num_crtcs, sizeof(*dev->vblank), GFP_KERNEL);
	if (!dev->vblank)
		goto err;

	for (i = 0; i < num_crtcs; i++) {
		struct drm_vblank_crtc *vblank = &dev->vblank[i];

		vblank->dev = dev;
		vblank->pipe = i;
		init_waitqueue_head(&vblank->queue);
		timer_setup(&vblank->disable_timer, vblank_disable_fn, 0);
		seqlock_init(&vblank->seqlock);
	}

	DRM_INFO("Supports vblank timestamp caching Rev 2 (21.10.2013).\n");

	/* Driver specific high-precision vblank timestamping supported? */
	if (dev->driver->get_vblank_timestamp)
		DRM_INFO("Driver supports precise vblank timestamp query.\n");
	else
		DRM_INFO("No driver support for vblank timestamp query.\n");

	/* Must have precise timestamping for reliable vblank instant disable */
	if (dev->vblank_disable_immediate && !dev->driver->get_vblank_timestamp) {
		dev->vblank_disable_immediate = false;
		DRM_INFO("Setting vblank_disable_immediate to false because "
			 "get_vblank_timestamp == NULL\n");
	}

	return 0;

err:
	dev->num_crtcs = 0;
	return ret;
}