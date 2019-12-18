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
typedef  int /*<<< orphan*/  u32 ;
struct mdp5_pipeline {scalar_t__ r_mixer; struct mdp5_hw_mixer* mixer; } ;
struct mdp5_hw_mixer {int /*<<< orphan*/  lm; } ;
struct mdp5_ctl_manager {TYPE_1__* dev; } ;
struct mdp5_ctl {int cursor_on; int /*<<< orphan*/  pending_ctl_trigger; int /*<<< orphan*/  hw_lock; int /*<<< orphan*/  id; struct mdp5_ctl_manager* ctlm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDP5_CTL_LAYER_REG_CURSOR_OUT ; 
 int /*<<< orphan*/  REG_MDP5_CTL_LAYER_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ctl_read (struct mdp5_ctl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_write (struct mdp5_ctl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_ctl_flush_mask_cursor (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int mdp5_ctl_set_cursor(struct mdp5_ctl *ctl, struct mdp5_pipeline *pipeline,
			int cursor_id, bool enable)
{
	struct mdp5_ctl_manager *ctl_mgr = ctl->ctlm;
	unsigned long flags;
	u32 blend_cfg;
	struct mdp5_hw_mixer *mixer = pipeline->mixer;

	if (WARN_ON(!mixer)) {
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "CTL %d cannot find LM",
			ctl->id);
		return -EINVAL;
	}

	if (pipeline->r_mixer) {
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "unsupported configuration");
		return -EINVAL;
	}

	spin_lock_irqsave(&ctl->hw_lock, flags);

	blend_cfg = ctl_read(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, mixer->lm));

	if (enable)
		blend_cfg |=  MDP5_CTL_LAYER_REG_CURSOR_OUT;
	else
		blend_cfg &= ~MDP5_CTL_LAYER_REG_CURSOR_OUT;

	ctl_write(ctl, REG_MDP5_CTL_LAYER_REG(ctl->id, mixer->lm), blend_cfg);
	ctl->cursor_on = enable;

	spin_unlock_irqrestore(&ctl->hw_lock, flags);

	ctl->pending_ctl_trigger = mdp_ctl_flush_mask_cursor(cursor_id);

	return 0;
}