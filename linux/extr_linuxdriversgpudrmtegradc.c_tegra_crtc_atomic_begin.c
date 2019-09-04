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
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* state; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * event; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_arm_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tegra_crtc_atomic_begin(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_crtc_state)
{
	unsigned long flags;

	if (crtc->state->event) {
		spin_lock_irqsave(&crtc->dev->event_lock, flags);

		if (drm_crtc_vblank_get(crtc) != 0)
			drm_crtc_send_vblank_event(crtc, crtc->state->event);
		else
			drm_crtc_arm_vblank_event(crtc, crtc->state->event);

		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);

		crtc->state->event = NULL;
	}
}