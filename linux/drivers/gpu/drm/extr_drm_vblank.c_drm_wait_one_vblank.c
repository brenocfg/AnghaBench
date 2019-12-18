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
typedef  scalar_t__ u64 ;
struct drm_vblank_crtc {int /*<<< orphan*/  queue; } ;
struct drm_device {unsigned int num_crtcs; struct drm_vblank_crtc* vblank; } ;

/* Variables and functions */
 scalar_t__ WARN (int,char*,unsigned int,...) ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ drm_vblank_count (struct drm_device*,unsigned int) ; 
 int drm_vblank_get (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  drm_vblank_put (struct drm_device*,unsigned int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void drm_wait_one_vblank(struct drm_device *dev, unsigned int pipe)
{
	struct drm_vblank_crtc *vblank = &dev->vblank[pipe];
	int ret;
	u64 last;

	if (WARN_ON(pipe >= dev->num_crtcs))
		return;

	ret = drm_vblank_get(dev, pipe);
	if (WARN(ret, "vblank not available on crtc %i, ret=%i\n", pipe, ret))
		return;

	last = drm_vblank_count(dev, pipe);

	ret = wait_event_timeout(vblank->queue,
				 last != drm_vblank_count(dev, pipe),
				 msecs_to_jiffies(100));

	WARN(ret == 0, "vblank wait timed out on crtc %i\n", pipe);

	drm_vblank_put(dev, pipe);
}