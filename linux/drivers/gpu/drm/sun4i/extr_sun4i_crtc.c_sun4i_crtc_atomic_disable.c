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
struct sun4i_crtc {int /*<<< orphan*/  tcon; } ;
struct drm_encoder {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_2__* state; TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * event; int /*<<< orphan*/  active; } ;
struct TYPE_3__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 struct sun4i_crtc* drm_crtc_to_sun4i_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct drm_encoder* sun4i_crtc_get_encoder (struct drm_crtc*) ; 
 int /*<<< orphan*/  sun4i_tcon_set_status (int /*<<< orphan*/ ,struct drm_encoder*,int) ; 

__attribute__((used)) static void sun4i_crtc_atomic_disable(struct drm_crtc *crtc,
				      struct drm_crtc_state *old_state)
{
	struct drm_encoder *encoder = sun4i_crtc_get_encoder(crtc);
	struct sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);

	DRM_DEBUG_DRIVER("Disabling the CRTC\n");

	drm_crtc_vblank_off(crtc);

	sun4i_tcon_set_status(scrtc->tcon, encoder, false);

	if (crtc->state->event && !crtc->state->active) {
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		spin_unlock_irq(&crtc->dev->event_lock);

		crtc->state->event = NULL;
	}
}