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
struct mdp5_pipeline {int dummy; } ;
struct mdp5_ctl {int dummy; } ;
struct mdp5_crtc_state {struct mdp5_ctl* ctl; struct mdp5_pipeline pipeline; } ;
struct mdp5_crtc {struct drm_pending_vblank_event* event; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_file {int dummy; } ;
struct drm_device {int /*<<< orphan*/  event_lock; } ;
struct drm_crtc {TYPE_1__* state; int /*<<< orphan*/  name; struct drm_device* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  drm_crtc_send_vblank_event (struct drm_crtc*,struct drm_pending_vblank_event*) ; 
 int /*<<< orphan*/  mdp5_ctl_blend (struct mdp5_ctl*,struct mdp5_pipeline*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (TYPE_1__*) ; 

__attribute__((used)) static void complete_flip(struct drm_crtc *crtc, struct drm_file *file)
{
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	struct mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	struct mdp5_ctl *ctl = mdp5_cstate->ctl;
	struct drm_device *dev = crtc->dev;
	struct drm_pending_vblank_event *event;
	unsigned long flags;

	spin_lock_irqsave(&dev->event_lock, flags);
	event = mdp5_crtc->event;
	if (event) {
		mdp5_crtc->event = NULL;
		DBG("%s: send event: %p", crtc->name, event);
		drm_crtc_send_vblank_event(crtc, event);
	}
	spin_unlock_irqrestore(&dev->event_lock, flags);

	if (ctl && !crtc->state->enable) {
		/* set STAGE_UNUSED for all layers */
		mdp5_ctl_blend(ctl, pipeline, NULL, NULL, 0, 0);
		/* XXX: What to do here? */
		/* mdp5_crtc->ctl = NULL; */
	}
}