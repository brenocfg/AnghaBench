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
struct sunxi_engine {TYPE_2__* ops; } ;
struct sun4i_crtc {int /*<<< orphan*/ * event; struct sunxi_engine* engine; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; struct drm_device* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* atomic_begin ) (struct sunxi_engine*,struct drm_crtc_state*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct sun4i_crtc* drm_crtc_to_sun4i_crtc (struct drm_crtc*) ; 
 scalar_t__ drm_crtc_vblank_get (struct drm_crtc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sunxi_engine*,struct drm_crtc_state*) ; 

__attribute__((used)) static void sun4i_crtc_atomic_begin(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct sun4i_crtc *scrtc = drm_crtc_to_sun4i_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct sunxi_engine *engine = scrtc->engine;
	unsigned long flags;

	if (crtc->state->event) {
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);

		spin_lock_irqsave(&dev->event_lock, flags);
		scrtc->event = crtc->state->event;
		spin_unlock_irqrestore(&dev->event_lock, flags);
		crtc->state->event = NULL;
	}

	if (engine->ops->atomic_begin)
		engine->ops->atomic_begin(engine, old_state);
}