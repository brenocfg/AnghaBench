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
typedef  int /*<<< orphan*/  uint32_t ;
struct omap_crtc {int pending; int /*<<< orphan*/  pending_wait; int /*<<< orphan*/ * event; int /*<<< orphan*/  framedone_handler_data; int /*<<< orphan*/  (* framedone_handler ) (int /*<<< orphan*/ ) ;} ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct omap_crtc* to_omap_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void omap_crtc_framedone_irq(struct drm_crtc *crtc, uint32_t irqstatus)
{
	struct omap_crtc *omap_crtc = to_omap_crtc(crtc);

	if (!omap_crtc->framedone_handler)
		return;

	omap_crtc->framedone_handler(omap_crtc->framedone_handler_data);

	spin_lock(&crtc->dev->event_lock);
	/* Send the vblank event if one has been requested. */
	if (omap_crtc->event) {
		drm_crtc_send_vblank_event(crtc, omap_crtc->event);
		omap_crtc->event = NULL;
	}
	omap_crtc->pending = false;
	spin_unlock(&crtc->dev->event_lock);

	/* Wake up omap_atomic_complete. */
	wake_up(&omap_crtc->pending_wait);
}