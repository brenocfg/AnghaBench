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
struct meson_crtc {int /*<<< orphan*/ * event; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; TYPE_2__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct meson_crtc* to_meson_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void meson_crtc_atomic_begin(struct drm_crtc *crtc,
				    struct drm_crtc_state *state)
{
	struct meson_crtc *meson_crtc = to_meson_crtc(crtc);
	unsigned long flags;

	if (crtc->state->event) {
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irqsave(&crtc->dev->event_lock, flags);
		meson_crtc->event = crtc->state->event;
		spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		crtc->state->event = NULL;
	}
}