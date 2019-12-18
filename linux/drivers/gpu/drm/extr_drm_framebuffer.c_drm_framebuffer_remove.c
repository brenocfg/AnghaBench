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
struct drm_framebuffer {int /*<<< orphan*/  filp_head; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_remove_fb (struct drm_framebuffer*) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 int drm_framebuffer_read_refcount (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  legacy_remove_fb (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void drm_framebuffer_remove(struct drm_framebuffer *fb)
{
	struct drm_device *dev;

	if (!fb)
		return;

	dev = fb->dev;

	WARN_ON(!list_empty(&fb->filp_head));

	/*
	 * drm ABI mandates that we remove any deleted framebuffers from active
	 * useage. But since most sane clients only remove framebuffers they no
	 * longer need, try to optimize this away.
	 *
	 * Since we're holding a reference ourselves, observing a refcount of 1
	 * means that we're the last holder and can skip it. Also, the refcount
	 * can never increase from 1 again, so we don't need any barriers or
	 * locks.
	 *
	 * Note that userspace could try to race with use and instate a new
	 * usage _after_ we've cleared all current ones. End result will be an
	 * in-use fb with fb-id == 0. Userspace is allowed to shoot its own foot
	 * in this manner.
	 */
	if (drm_framebuffer_read_refcount(fb) > 1) {
		if (drm_drv_uses_atomic_modeset(dev)) {
			int ret = atomic_remove_fb(fb);
			WARN(ret, "atomic remove_fb failed with %i\n", ret);
		} else
			legacy_remove_fb(fb);
	}

	drm_framebuffer_put(fb);
}