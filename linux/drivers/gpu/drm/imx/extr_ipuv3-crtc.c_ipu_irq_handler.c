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
struct ipu_plane {int /*<<< orphan*/  base; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct ipu_crtc {int /*<<< orphan*/ * event; struct ipu_plane** plane; struct drm_crtc base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  event_lock; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct ipu_plane**) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  drm_crtc_handle_vblank (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 scalar_t__ ipu_plane_atomic_update_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t ipu_irq_handler(int irq, void *dev_id)
{
	struct ipu_crtc *ipu_crtc = dev_id;
	struct drm_crtc *crtc = &ipu_crtc->base;
	unsigned long flags;
	int i;

	drm_crtc_handle_vblank(crtc);

	if (ipu_crtc->event) {
		for (i = 0; i < ARRAY_SIZE(ipu_crtc->plane); i++) {
			struct ipu_plane *plane = ipu_crtc->plane[i];

			if (!plane)
				continue;

			if (ipu_plane_atomic_update_pending(&plane->base))
				break;
		}

		if (i == ARRAY_SIZE(ipu_crtc->plane)) {
			spin_lock_irqsave(&crtc->dev->event_lock, flags);
			drm_crtc_send_vblank_event(crtc, ipu_crtc->event);
			ipu_crtc->event = NULL;
			drm_crtc_vblank_put(crtc);
			spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
		}
	}

	return IRQ_HANDLED;
}