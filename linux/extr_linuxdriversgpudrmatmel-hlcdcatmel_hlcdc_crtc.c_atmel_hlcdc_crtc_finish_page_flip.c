#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct TYPE_3__ {struct drm_device* dev; } ;
struct atmel_hlcdc_crtc {int /*<<< orphan*/ * event; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_send_vblank_event (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void atmel_hlcdc_crtc_finish_page_flip(struct atmel_hlcdc_crtc *crtc)
{
	struct drm_device *dev = crtc->base.dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	if (crtc->event) {
		drm_crtc_send_vblank_event(&crtc->base, crtc->event);
		drm_crtc_vblank_put(&crtc->base);
		crtc->event = NULL;
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);
}