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
struct vc4_crtc {TYPE_2__* event; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  pipe; } ;
struct TYPE_3__ {TYPE_2__* event; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  drm_crtc_index (struct drm_crtc*) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void vc4_crtc_atomic_flush(struct drm_crtc *crtc,
				  struct drm_crtc_state *old_state)
{
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	struct drm_device *dev = crtc->dev;

	if (crtc->state->event) {
		unsigned long flags;

		crtc->state->event->pipe = drm_crtc_index(crtc);

		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irqsave(&dev->event_lock, flags);
		vc4_crtc->event = crtc->state->event;
		crtc->state->event = NULL;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	}
}