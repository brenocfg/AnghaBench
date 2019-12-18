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
struct tilcdc_crtc {int /*<<< orphan*/  enable_lock; int /*<<< orphan*/  irq_lock; struct drm_framebuffer* next_fb; int /*<<< orphan*/  hvtotal_us; int /*<<< orphan*/  last_vblank; scalar_t__ enabled; struct drm_pending_vblank_event* event; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {struct drm_device* dev; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ TILCDC_VBLANK_SAFETY_THRESHOLD_US ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_add_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_scanout (struct drm_crtc*,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct tilcdc_crtc* to_tilcdc_crtc (struct drm_crtc*) ; 

int tilcdc_crtc_update_fb(struct drm_crtc *crtc,
		struct drm_framebuffer *fb,
		struct drm_pending_vblank_event *event)
{
	struct tilcdc_crtc *tilcdc_crtc = to_tilcdc_crtc(crtc);
	struct drm_device *dev = crtc->dev;

	if (tilcdc_crtc->event) {
		dev_err(dev->dev, "already pending page flip!\n");
		return -EBUSY;
	}

	tilcdc_crtc->event = event;

	mutex_lock(&tilcdc_crtc->enable_lock);

	if (tilcdc_crtc->enabled) {
		unsigned long flags;
		ktime_t next_vblank;
		s64 tdiff;

		spin_lock_irqsave(&tilcdc_crtc->irq_lock, flags);

		next_vblank = ktime_add_us(tilcdc_crtc->last_vblank,
					   tilcdc_crtc->hvtotal_us);
		tdiff = ktime_to_us(ktime_sub(next_vblank, ktime_get()));

		if (tdiff < TILCDC_VBLANK_SAFETY_THRESHOLD_US)
			tilcdc_crtc->next_fb = fb;
		else
			set_scanout(crtc, fb);

		spin_unlock_irqrestore(&tilcdc_crtc->irq_lock, flags);
	}

	mutex_unlock(&tilcdc_crtc->enable_lock);

	return 0;
}