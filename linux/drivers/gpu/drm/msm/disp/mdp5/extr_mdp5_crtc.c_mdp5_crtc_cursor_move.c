#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mdp5_kms {TYPE_3__* pdev; } ;
struct TYPE_5__ {scalar_t__ r_mixer; } ;
struct mdp5_crtc_state {TYPE_1__ pipeline; } ;
struct TYPE_6__ {int x; int y; int /*<<< orphan*/  lock; scalar_t__ height; scalar_t__ width; } ;
struct mdp5_crtc {TYPE_2__ cursor; int /*<<< orphan*/  lm_cursor_enabled; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
struct drm_crtc {TYPE_4__* state; struct drm_device* dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  enable; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  crtc_flush (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 struct mdp5_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  get_roi (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  mdp5_crtc_restore_cursor (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp_ctl_flush_mask_cursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int mdp5_crtc_cursor_move(struct drm_crtc *crtc, int x, int y)
{
	struct mdp5_kms *mdp5_kms = get_kms(crtc);
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	uint32_t flush_mask = mdp_ctl_flush_mask_cursor(0);
	struct drm_device *dev = crtc->dev;
	uint32_t roi_w;
	uint32_t roi_h;
	unsigned long flags;

	if (!mdp5_crtc->lm_cursor_enabled) {
		dev_warn(dev->dev,
			 "cursor_move is deprecated with cursor planes\n");
		return -EINVAL;
	}

	/* don't support LM cursors when we we have source split enabled */
	if (mdp5_cstate->pipeline.r_mixer)
		return -EINVAL;

	/* In case the CRTC is disabled, just drop the cursor update */
	if (unlikely(!crtc->state->enable))
		return 0;

	/* accept negative x/y coordinates up to maximum cursor overlap */
	mdp5_crtc->cursor.x = x = max(x, -(int)mdp5_crtc->cursor.width);
	mdp5_crtc->cursor.y = y = max(y, -(int)mdp5_crtc->cursor.height);

	get_roi(crtc, &roi_w, &roi_h);

	pm_runtime_get_sync(&mdp5_kms->pdev->dev);

	spin_lock_irqsave(&mdp5_crtc->cursor.lock, flags);
	mdp5_crtc_restore_cursor(crtc);
	spin_unlock_irqrestore(&mdp5_crtc->cursor.lock, flags);

	crtc_flush(crtc, flush_mask);

	pm_runtime_put_sync(&mdp5_kms->pdev->dev);

	return 0;
}