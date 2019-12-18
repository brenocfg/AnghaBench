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
struct TYPE_4__ {int /*<<< orphan*/  scaler_id; } ;
struct drm_display_mode {int /*<<< orphan*/  crtc_vdisplay; int /*<<< orphan*/  crtc_hdisplay; } ;
struct TYPE_3__ {int /*<<< orphan*/  active; struct drm_display_mode adjusted_mode; } ;
struct intel_crtc_state {scalar_t__ output_format; int /*<<< orphan*/  pipe_src_h; int /*<<< orphan*/  pipe_src_w; TYPE_2__ scaler_state; TYPE_1__ base; } ;

/* Variables and functions */
 scalar_t__ INTEL_OUTPUT_FORMAT_YCBCR420 ; 
 int /*<<< orphan*/  SKL_CRTC_INDEX ; 
 int skl_update_scaler (struct intel_crtc_state*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int skl_update_scaler_crtc(struct intel_crtc_state *state)
{
	const struct drm_display_mode *adjusted_mode = &state->base.adjusted_mode;
	bool need_scaler = false;

	if (state->output_format == INTEL_OUTPUT_FORMAT_YCBCR420)
		need_scaler = true;

	return skl_update_scaler(state, !state->base.active, SKL_CRTC_INDEX,
				 &state->scaler_state.scaler_id,
				 state->pipe_src_w, state->pipe_src_h,
				 adjusted_mode->crtc_hdisplay,
				 adjusted_mode->crtc_vdisplay, NULL, need_scaler);
}