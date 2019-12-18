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
struct drm_display_mode {int hdisplay; int /*<<< orphan*/  vdisplay; } ;
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct drm_crtc {int dummy; } ;
struct dpu_crtc_state {int num_mixers; struct drm_rect* lm_bounds; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRMID (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_mode_debug_printmodeline (struct drm_display_mode*) ; 
 struct dpu_crtc_state* to_dpu_crtc_state (struct drm_crtc_state*) ; 
 int /*<<< orphan*/  trace_dpu_crtc_setup_lm_bounds (int /*<<< orphan*/ ,int,struct drm_rect*) ; 

__attribute__((used)) static void _dpu_crtc_setup_lm_bounds(struct drm_crtc *crtc,
		struct drm_crtc_state *state)
{
	struct dpu_crtc_state *cstate = to_dpu_crtc_state(state);
	struct drm_display_mode *adj_mode = &state->adjusted_mode;
	u32 crtc_split_width = adj_mode->hdisplay / cstate->num_mixers;
	int i;

	for (i = 0; i < cstate->num_mixers; i++) {
		struct drm_rect *r = &cstate->lm_bounds[i];
		r->x1 = crtc_split_width * i;
		r->y1 = 0;
		r->x2 = r->x1 + crtc_split_width;
		r->y2 = adj_mode->vdisplay;

		trace_dpu_crtc_setup_lm_bounds(DRMID(crtc), i, r);
	}

	drm_mode_debug_printmodeline(adj_mode);
}