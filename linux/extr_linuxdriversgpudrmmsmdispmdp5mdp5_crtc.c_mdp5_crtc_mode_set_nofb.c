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
typedef  int uint32_t ;
typedef  int u32 ;
struct mdp5_kms {int dummy; } ;
struct mdp5_hw_mixer {int lm; } ;
struct TYPE_4__ {struct mdp5_hw_mixer* r_mixer; struct mdp5_hw_mixer* mixer; } ;
struct mdp5_crtc_state {TYPE_1__ pipeline; } ;
struct mdp5_crtc {int /*<<< orphan*/  lm_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  id; } ;
struct drm_display_mode {int hdisplay; int /*<<< orphan*/  vdisplay; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; int /*<<< orphan*/  vtotal; int /*<<< orphan*/  vsync_end; int /*<<< orphan*/  vsync_start; int /*<<< orphan*/  htotal; int /*<<< orphan*/  hsync_end; int /*<<< orphan*/  hsync_start; int /*<<< orphan*/  clock; int /*<<< orphan*/  vrefresh; int /*<<< orphan*/  name; TYPE_2__ base; } ;
struct drm_crtc {int /*<<< orphan*/  name; TYPE_3__* state; } ;
struct TYPE_6__ {struct drm_display_mode adjusted_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MDP5_LM_BLEND_COLOR_OUT_SPLIT_LEFT_RIGHT ; 
 int MDP5_LM_OUT_SIZE_HEIGHT (int /*<<< orphan*/ ) ; 
 int MDP5_LM_OUT_SIZE_WIDTH (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_BLEND_COLOR_OUT (int) ; 
 int /*<<< orphan*/  REG_MDP5_LM_OUT_SIZE (int) ; 
 scalar_t__ WARN_ON (int) ; 
 struct mdp5_kms* get_kms (struct drm_crtc*) ; 
 int mdp5_read (struct mdp5_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mdp5_crtc* to_mdp5_crtc (struct drm_crtc*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (TYPE_3__*) ; 

__attribute__((used)) static void mdp5_crtc_mode_set_nofb(struct drm_crtc *crtc)
{
	struct mdp5_crtc *mdp5_crtc = to_mdp5_crtc(crtc);
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	struct mdp5_kms *mdp5_kms = get_kms(crtc);
	struct mdp5_hw_mixer *mixer = mdp5_cstate->pipeline.mixer;
	struct mdp5_hw_mixer *r_mixer = mdp5_cstate->pipeline.r_mixer;
	uint32_t lm = mixer->lm;
	u32 mixer_width, val;
	unsigned long flags;
	struct drm_display_mode *mode;

	if (WARN_ON(!crtc->state))
		return;

	mode = &crtc->state->adjusted_mode;

	DBG("%s: set mode: %d:\"%s\" %d %d %d %d %d %d %d %d %d %d 0x%x 0x%x",
			crtc->name, mode->base.id, mode->name,
			mode->vrefresh, mode->clock,
			mode->hdisplay, mode->hsync_start,
			mode->hsync_end, mode->htotal,
			mode->vdisplay, mode->vsync_start,
			mode->vsync_end, mode->vtotal,
			mode->type, mode->flags);

	mixer_width = mode->hdisplay;
	if (r_mixer)
		mixer_width /= 2;

	spin_lock_irqsave(&mdp5_crtc->lm_lock, flags);
	mdp5_write(mdp5_kms, REG_MDP5_LM_OUT_SIZE(lm),
			MDP5_LM_OUT_SIZE_WIDTH(mixer_width) |
			MDP5_LM_OUT_SIZE_HEIGHT(mode->vdisplay));

	/* Assign mixer to LEFT side in source split mode */
	val = mdp5_read(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(lm));
	val &= ~MDP5_LM_BLEND_COLOR_OUT_SPLIT_LEFT_RIGHT;
	mdp5_write(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(lm), val);

	if (r_mixer) {
		u32 r_lm = r_mixer->lm;

		mdp5_write(mdp5_kms, REG_MDP5_LM_OUT_SIZE(r_lm),
			   MDP5_LM_OUT_SIZE_WIDTH(mixer_width) |
			   MDP5_LM_OUT_SIZE_HEIGHT(mode->vdisplay));

		/* Assign mixer to RIGHT side in source split mode */
		val = mdp5_read(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(r_lm));
		val |= MDP5_LM_BLEND_COLOR_OUT_SPLIT_LEFT_RIGHT;
		mdp5_write(mdp5_kms, REG_MDP5_LM_BLEND_COLOR_OUT(r_lm), val);
	}

	spin_unlock_irqrestore(&mdp5_crtc->lm_lock, flags);
}