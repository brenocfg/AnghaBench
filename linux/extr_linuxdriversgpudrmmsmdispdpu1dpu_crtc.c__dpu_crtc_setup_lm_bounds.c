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
typedef  int u32 ;
struct drm_rect {int x1; int x2; int /*<<< orphan*/  y2; scalar_t__ y1; } ;
struct drm_display_mode {int dummy; } ;
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct drm_crtc {int dummy; } ;
struct dpu_crtc_state {struct drm_rect* lm_bounds; } ;
struct dpu_crtc {int num_mixers; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*) ; 
 int /*<<< orphan*/  DRMID (struct drm_crtc*) ; 
 int /*<<< orphan*/  dpu_crtc_get_mixer_height (struct dpu_crtc*,struct dpu_crtc_state*,struct drm_display_mode*) ; 
 int dpu_crtc_get_mixer_width (struct dpu_crtc*,struct dpu_crtc_state*,struct drm_display_mode*) ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 
 struct dpu_crtc* to_dpu_crtc (struct drm_crtc*) ; 
 struct dpu_crtc_state* to_dpu_crtc_state (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  trace_dpu_crtc_setup_lm_bounds (int /*<<< orphan*/ ,int,struct drm_rect*) ; 

__attribute__((used)) static void _dpu_crtc_setup_lm_bounds(struct drm_crtc *crtc,
		struct drm_crtc_state *state)
{
	struct dpu_crtc *dpu_crtc;
	struct dpu_crtc_state *cstate;
	struct drm_display_mode *adj_mode;
	u32 crtc_split_width;
	int i;

	if (!crtc || !state) {
		DPU_ERROR("invalid args\n");
		return;
	}

	dpu_crtc = to_dpu_crtc(crtc);
	cstate = to_dpu_crtc_state(state);

	adj_mode = &state->adjusted_mode;
	crtc_split_width = dpu_crtc_get_mixer_width(dpu_crtc, cstate, adj_mode);

	for (i = 0; i < dpu_crtc->num_mixers; i++) {
		struct drm_rect *r = &cstate->lm_bounds[i];
		r->x1 = crtc_split_width * i;
		r->y1 = 0;
		r->x2 = r->x1 + crtc_split_width;
		r->y2 = dpu_crtc_get_mixer_height(dpu_crtc, cstate, adj_mode);

		trace_dpu_crtc_setup_lm_bounds(DRMID(crtc), i, r);
	}

	drm_mode_debug_printmodeline(adj_mode);
}