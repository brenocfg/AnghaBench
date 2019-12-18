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
struct drm_pending_vblank_event {unsigned int pipe; } ;
struct drm_device {scalar_t__ num_crtcs; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 unsigned int drm_crtc_index (struct drm_crtc*) ; 
 scalar_t__ drm_vblank_count_and_time (struct drm_device*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  send_vblank_event (struct drm_device*,struct drm_pending_vblank_event*,scalar_t__,int /*<<< orphan*/ ) ; 

void drm_crtc_send_vblank_event(struct drm_crtc *crtc,
				struct drm_pending_vblank_event *e)
{
	struct drm_device *dev = crtc->dev;
	u64 seq;
	unsigned int pipe = drm_crtc_index(crtc);
	ktime_t now;

	if (dev->num_crtcs > 0) {
		seq = drm_vblank_count_and_time(dev, pipe, &now);
	} else {
		seq = 0;

		now = ktime_get();
	}
	e->pipe = pipe;
	send_vblank_event(dev, e, seq, now);
}