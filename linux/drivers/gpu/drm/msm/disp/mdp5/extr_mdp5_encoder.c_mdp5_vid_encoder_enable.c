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
struct mdp5_pipeline {int dummy; } ;
struct mdp5_kms {int dummy; } ;
struct mdp5_interface {int num; } ;
struct mdp5_encoder {int enabled; int /*<<< orphan*/  intf_lock; struct mdp5_interface* intf; struct mdp5_ctl* ctl; } ;
struct mdp5_ctl {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_MDP5_INTF_TIMING_ENGINE_EN (int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bs_set (struct mdp5_encoder*,int) ; 
 struct mdp5_kms* get_kms (struct drm_encoder*) ; 
 struct mdp5_pipeline* mdp5_crtc_get_pipeline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_ctl_commit (struct mdp5_ctl*,struct mdp5_pipeline*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp5_ctl_set_encoder_state (struct mdp5_ctl*,struct mdp5_pipeline*,int) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp_ctl_flush_mask_encoder (struct mdp5_interface*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp5_vid_encoder_enable(struct drm_encoder *encoder)
{
	struct mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	struct mdp5_kms *mdp5_kms = get_kms(encoder);
	struct mdp5_ctl *ctl = mdp5_encoder->ctl;
	struct mdp5_interface *intf = mdp5_encoder->intf;
	struct mdp5_pipeline *pipeline = mdp5_crtc_get_pipeline(encoder->crtc);
	int intfn = intf->num;
	unsigned long flags;

	if (WARN_ON(mdp5_encoder->enabled))
		return;

	bs_set(mdp5_encoder, 1);
	spin_lock_irqsave(&mdp5_encoder->intf_lock, flags);
	mdp5_write(mdp5_kms, REG_MDP5_INTF_TIMING_ENGINE_EN(intfn), 1);
	spin_unlock_irqrestore(&mdp5_encoder->intf_lock, flags);
	mdp5_ctl_commit(ctl, pipeline, mdp_ctl_flush_mask_encoder(intf), true);

	mdp5_ctl_set_encoder_state(ctl, pipeline, true);

	mdp5_encoder->enabled = true;
}