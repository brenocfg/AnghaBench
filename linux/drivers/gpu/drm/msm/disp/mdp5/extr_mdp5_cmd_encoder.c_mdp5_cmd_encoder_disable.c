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
struct mdp5_interface {int dummy; } ;
struct mdp5_encoder {int enabled; struct mdp5_interface* intf; struct mdp5_ctl* ctl; } ;
struct mdp5_ctl {int dummy; } ;
struct drm_encoder {int /*<<< orphan*/  crtc; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bs_set (struct mdp5_encoder*,int /*<<< orphan*/ ) ; 
 struct mdp5_pipeline* mdp5_crtc_get_pipeline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_ctl_commit (struct mdp5_ctl*,struct mdp5_pipeline*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp5_ctl_set_encoder_state (struct mdp5_ctl*,struct mdp5_pipeline*,int) ; 
 int /*<<< orphan*/  mdp_ctl_flush_mask_encoder (struct mdp5_interface*) ; 
 int /*<<< orphan*/  pingpong_tearcheck_disable (struct drm_encoder*) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

void mdp5_cmd_encoder_disable(struct drm_encoder *encoder)
{
	struct mdp5_encoder *mdp5_cmd_enc = to_mdp5_encoder(encoder);
	struct mdp5_ctl *ctl = mdp5_cmd_enc->ctl;
	struct mdp5_interface *intf = mdp5_cmd_enc->intf;
	struct mdp5_pipeline *pipeline = mdp5_crtc_get_pipeline(encoder->crtc);

	if (WARN_ON(!mdp5_cmd_enc->enabled))
		return;

	pingpong_tearcheck_disable(encoder);

	mdp5_ctl_set_encoder_state(ctl, pipeline, false);
	mdp5_ctl_commit(ctl, pipeline, mdp_ctl_flush_mask_encoder(intf), true);

	bs_set(mdp5_cmd_enc, 0);

	mdp5_cmd_enc->enabled = false;
}