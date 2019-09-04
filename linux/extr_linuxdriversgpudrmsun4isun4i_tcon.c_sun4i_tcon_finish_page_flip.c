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
struct sun4i_crtc {int /*<<< orphan*/ * event; int /*<<< orphan*/  crtc; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_send_vblank_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void sun4i_tcon_finish_page_flip(struct drm_device *dev,
					struct sun4i_crtc *scrtc)
{
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	if (scrtc->event) {
		drm_crtc_send_vblank_event(&scrtc->crtc, scrtc->event);
		drm_crtc_vblank_put(&scrtc->crtc);
		scrtc->event = NULL;
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);
}