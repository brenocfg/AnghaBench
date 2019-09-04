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
struct vc4_crtc {TYPE_1__* event; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc {struct drm_device* dev; } ;
struct TYPE_4__ {struct drm_file* file_priv; } ;
struct TYPE_3__ {TYPE_2__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_crtc_vblank_put (struct drm_crtc*) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct vc4_crtc* to_vc4_crtc (struct drm_crtc*) ; 

void vc4_fkms_cancel_page_flip(struct drm_crtc *crtc, struct drm_file *file)
{
	struct vc4_crtc *vc4_crtc = to_vc4_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);

	if (vc4_crtc->event && vc4_crtc->event->base.file_priv == file) {
		kfree(&vc4_crtc->event->base);
		drm_crtc_vblank_put(crtc);
		vc4_crtc->event = NULL;
	}

	spin_unlock_irqrestore(&dev->event_lock, flags);
}