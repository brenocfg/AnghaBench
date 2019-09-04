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
struct mdp4_crtc {int /*<<< orphan*/ * event; int /*<<< orphan*/  name; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_1__* state; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * event; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PENDING_FLIP ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blend_setup (struct drm_crtc*) ; 
 int /*<<< orphan*/  crtc_flush (struct drm_crtc*) ; 
 int /*<<< orphan*/  request_pending (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp4_crtc* to_mdp4_crtc (struct drm_crtc*) ; 

__attribute__((used)) static void mdp4_crtc_atomic_flush(struct drm_crtc *crtc,
				   struct drm_crtc_state *old_crtc_state)
{
	struct mdp4_crtc *mdp4_crtc = to_mdp4_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	unsigned long flags;

	DBG("%s: event: %p", mdp4_crtc->name, crtc->state->event);

	WARN_ON(mdp4_crtc->event);

	spin_lock_irqsave(&dev->event_lock, flags);
	mdp4_crtc->event = crtc->state->event;
	crtc->state->event = NULL;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	blend_setup(crtc);
	crtc_flush(crtc);
	request_pending(crtc, PENDING_FLIP);
}