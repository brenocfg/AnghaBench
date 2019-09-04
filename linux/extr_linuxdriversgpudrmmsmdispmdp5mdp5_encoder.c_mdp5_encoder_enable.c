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
struct mdp5_interface {scalar_t__ mode; } ;
struct mdp5_encoder {struct mdp5_interface* intf; } ;
struct drm_encoder {TYPE_1__* crtc; } ;
struct drm_crtc_state {int /*<<< orphan*/  adjusted_mode; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {struct drm_crtc_state* state; } ;

/* Variables and functions */
 scalar_t__ MDP5_INTF_DSI_MODE_COMMAND ; 
 int /*<<< orphan*/  mdp5_cmd_encoder_enable (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp5_encoder_mode_set (struct drm_encoder*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdp5_vid_encoder_enable (struct drm_encoder*) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

__attribute__((used)) static void mdp5_encoder_enable(struct drm_encoder *encoder)
{
	struct mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	struct mdp5_interface *intf = mdp5_encoder->intf;
	/* this isn't right I think */
	struct drm_crtc_state *cstate = encoder->crtc->state;

	mdp5_encoder_mode_set(encoder, &cstate->mode, &cstate->adjusted_mode);

	if (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)
		mdp5_cmd_encoder_enable(encoder);
	else
		mdp5_vid_encoder_enable(encoder);
}