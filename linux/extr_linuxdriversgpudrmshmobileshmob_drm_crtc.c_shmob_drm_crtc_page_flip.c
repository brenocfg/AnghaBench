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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {struct drm_device* dev; } ;
struct shmob_drm_crtc {struct drm_pending_vblank_event* event; TYPE_2__ crtc; } ;
struct drm_pending_vblank_event {scalar_t__ pipe; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc {TYPE_1__* primary; } ;
struct TYPE_3__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  drm_crtc_vblank_get (TYPE_2__*) ; 
 int /*<<< orphan*/  shmob_drm_crtc_update_base (struct shmob_drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct shmob_drm_crtc* to_shmob_crtc (struct drm_crtc*) ; 

__attribute__((used)) static int shmob_drm_crtc_page_flip(struct drm_crtc *crtc,
				    struct drm_framebuffer *fb,
				    struct drm_pending_vblank_event *event,
				    uint32_t page_flip_flags,
				    struct drm_modeset_acquire_ctx *ctx)
{
	struct shmob_drm_crtc *scrtc = to_shmob_crtc(crtc);
	struct drm_device *dev = scrtc->crtc.dev;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	if (scrtc->event != NULL) {
		spin_unlock_irqrestore(&dev->event_lock, flags);
		return -EBUSY;
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);

	crtc->primary->fb = fb;
	shmob_drm_crtc_update_base(scrtc);

	if (event) {
		event->pipe = 0;
		drm_crtc_vblank_get(&scrtc->crtc);
		spin_lock_irqsave(&dev->event_lock, flags);
		scrtc->event = event;
		spin_unlock_irqrestore(&dev->event_lock, flags);
	}

	return 0;
}