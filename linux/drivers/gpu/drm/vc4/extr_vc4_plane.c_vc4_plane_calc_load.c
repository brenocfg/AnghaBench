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
struct vc4_plane_state {scalar_t__* x_scaling; scalar_t__* y_scaling; unsigned int membus_load; int hvs_load; unsigned int* src_h; int crtc_h; unsigned int* src_w; int crtc_w; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; struct drm_framebuffer* fb; } ;
struct drm_framebuffer {TYPE_1__* format; } ;
struct drm_crtc_state {int /*<<< orphan*/  adjusted_mode; } ;
struct TYPE_2__ {unsigned int num_planes; unsigned int* cpp; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_UP (unsigned int,int) ; 
 scalar_t__ VC4_SCALING_NONE ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int drm_mode_vrefresh (int /*<<< orphan*/ *) ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static void vc4_plane_calc_load(struct drm_plane_state *state)
{
	unsigned int hvs_load_shift, vrefresh, i;
	struct drm_framebuffer *fb = state->fb;
	struct vc4_plane_state *vc4_state;
	struct drm_crtc_state *crtc_state;
	unsigned int vscale_factor;

	vc4_state = to_vc4_plane_state(state);
	crtc_state = drm_atomic_get_existing_crtc_state(state->state,
							state->crtc);
	vrefresh = drm_mode_vrefresh(&crtc_state->adjusted_mode);

	/* The HVS is able to process 2 pixels/cycle when scaling the source,
	 * 4 pixels/cycle otherwise.
	 * Alpha blending step seems to be pipelined and it's always operating
	 * at 4 pixels/cycle, so the limiting aspect here seems to be the
	 * scaler block.
	 * HVS load is expressed in clk-cycles/sec (AKA Hz).
	 */
	if (vc4_state->x_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->x_scaling[1] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[0] != VC4_SCALING_NONE ||
	    vc4_state->y_scaling[1] != VC4_SCALING_NONE)
		hvs_load_shift = 1;
	else
		hvs_load_shift = 2;

	vc4_state->membus_load = 0;
	vc4_state->hvs_load = 0;
	for (i = 0; i < fb->format->num_planes; i++) {
		/* Even if the bandwidth/plane required for a single frame is
		 *
		 * vc4_state->src_w[i] * vc4_state->src_h[i] * cpp * vrefresh
		 *
		 * when downscaling, we have to read more pixels per line in
		 * the time frame reserved for a single line, so the bandwidth
		 * demand can be punctually higher. To account for that, we
		 * calculate the down-scaling factor and multiply the plane
		 * load by this number. We're likely over-estimating the read
		 * demand, but that's better than under-estimating it.
		 */
		vscale_factor = DIV_ROUND_UP(vc4_state->src_h[i],
					     vc4_state->crtc_h);
		vc4_state->membus_load += vc4_state->src_w[i] *
					  vc4_state->src_h[i] * vscale_factor *
					  fb->format->cpp[i];
		vc4_state->hvs_load += vc4_state->crtc_h * vc4_state->crtc_w;
	}

	vc4_state->hvs_load *= vrefresh;
	vc4_state->hvs_load >>= hvs_load_shift;
	vc4_state->membus_load *= vrefresh;
}