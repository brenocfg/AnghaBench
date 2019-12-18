#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mdp5_kms {TYPE_2__* dev; int /*<<< orphan*/  base; TYPE_1__* pdev; } ;
struct mdp5_crtc_state {scalar_t__ cmd_mode; } ;
struct mdp5_crtc {int enabled; int event; int /*<<< orphan*/  err; int /*<<< orphan*/  pp_done; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {TYPE_3__* state; int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * event; int /*<<< orphan*/  active; } ;
struct TYPE_5__ {int /*<<< orphan*/  event_lock; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_crtc_vblank_off (struct drm_crtc*) ; 
 struct mdp5_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp_irq_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (TYPE_3__*) ; 

__attribute__((used)) static void mdp5_crtc_atomic_disable(struct drm_crtc *crtc,
				     struct drm_crtc_state *old_state)
{
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	struct mdp5_kms *mdp5_kms = get_kms(crtc);
	struct device *dev = &mdp5_kms->pdev->dev;
	unsigned long flags;

	DBG("%s", crtc->name);

	if (WARN_ON(!mdp5_crtc->enabled))
		return;

	/* Disable/save vblank irq handling before power is disabled */
	drm_crtc_vblank_off(crtc);

	if (mdp5_cstate->cmd_mode)
		mdp_irq_unregister(&mdp5_kms->base, &mdp5_crtc->pp_done);

	mdp_irq_unregister(&mdp5_kms->base, &mdp5_crtc->err);
	pm_runtime_put_sync(dev);

	if (crtc->state->event && !crtc->state->active) {
		WARN_ON(mdp5_crtc->event);
		spin_lock_irqsave(&mdp5_kms->dev->event_lock, flags);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = NULL;
		spin_unlock_irqrestore(&mdp5_kms->dev->event_lock, flags);
	}

	mdp5_crtc->enabled = false;
}