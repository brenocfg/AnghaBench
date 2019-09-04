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
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct drm_pending_vblank_event {unsigned int pipe; TYPE_1__ base; scalar_t__ sequence; } ;
struct drm_device {int /*<<< orphan*/  vblank_event_list; int /*<<< orphan*/  event_lock; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_crtc_accurate_vblank_count (struct drm_crtc*) ; 
 unsigned int drm_crtc_index (struct drm_crtc*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void drm_crtc_arm_vblank_event(struct drm_crtc *crtc,
			       struct drm_pending_vblank_event *e)
{
	struct drm_device *dev = crtc->dev;
	unsigned int pipe = drm_crtc_index(crtc);

	assert_spin_locked(&dev->event_lock);

	e->pipe = pipe;
	e->sequence = drm_crtc_accurate_vblank_count(crtc) + 1;
	list_add_tail(&e->base.link, &dev->vblank_event_list);
}