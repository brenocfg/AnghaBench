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
struct mdp5_kms {int /*<<< orphan*/  base; TYPE_1__* pdev; } ;
struct mdp5_crtc_state {scalar_t__ cmd_mode; int /*<<< orphan*/  pipeline; int /*<<< orphan*/  ctl; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; scalar_t__ iova; } ;
struct mdp5_crtc {int enabled; int /*<<< orphan*/  pp_done; int /*<<< orphan*/  err; TYPE_2__ cursor; scalar_t__ lm_cursor_enabled; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  name; int /*<<< orphan*/  state; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct mdp5_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp5_crtc_mode_set_nofb (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp5_crtc_restore_cursor (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp5_crtc_vblank_on (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp5_ctl_set_cursor (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp_irq_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdp5_crtc_atomic_enable(struct drm_crtc *crtc,
				    struct drm_crtc_state *old_state)
{
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	struct mdp5_kms *mdp5_kms = get_kms(crtc);
	struct device *dev = &mdp5_kms->pdev->dev;

	DBG("%s", crtc->name);

	if (WARN_ON(mdp5_crtc->enabled))
		return;

	pm_runtime_get_sync(dev);

	if (mdp5_crtc->lm_cursor_enabled) {
		/*
		 * Restore LM cursor state, as it might have been lost
		 * with suspend:
		 */
		if (mdp5_crtc->cursor.iova) {
			unsigned long flags;

			spin_lock_irqsave(&mdp5_crtc->cursor.lock, flags);
			mdp5_crtc_restore_cursor(crtc);
			spin_unlock_irqrestore(&mdp5_crtc->cursor.lock, flags);

			mdp5_ctl_set_cursor(mdp5_cstate->ctl,
					    &mdp5_cstate->pipeline, 0, true);
		} else {
			mdp5_ctl_set_cursor(mdp5_cstate->ctl,
					    &mdp5_cstate->pipeline, 0, false);
		}
	}

	/* Restore vblank irq handling after power is enabled */
	mdp5_crtc_vblank_on(crtc);

	mdp5_crtc_mode_set_nofb(crtc);

	mdp_irq_register(&mdp5_kms->base, &mdp5_crtc->err);

	if (mdp5_cstate->cmd_mode)
		mdp_irq_register(&mdp5_kms->base, &mdp5_crtc->pp_done);

	mdp5_crtc->enabled = true;
}