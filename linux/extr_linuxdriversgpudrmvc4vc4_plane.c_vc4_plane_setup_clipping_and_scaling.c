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
typedef  int u32 ;
struct vc4_plane_state {int src_x; int src_y; int* src_w; int* src_h; int crtc_x; int crtc_y; scalar_t__* x_scaling; scalar_t__* y_scaling; int is_unity; int is_yuv; scalar_t__* offsets; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; } ;
struct drm_plane_state {int src_x; int src_y; int src_w; int src_h; int crtc_x; int crtc_y; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; struct drm_framebuffer* fb; struct drm_plane* plane; } ;
struct drm_plane {scalar_t__ type; } ;
struct drm_gem_cma_object {scalar_t__ paddr; } ;
struct drm_framebuffer {int* pitches; TYPE_1__* format; scalar_t__* offsets; } ;
struct TYPE_2__ {int format; int num_planes; int* cpp; } ;

/* Variables and functions */
 scalar_t__ DRM_PLANE_TYPE_CURSOR ; 
 int EINVAL ; 
 scalar_t__ VC4_SCALING_NONE ; 
 scalar_t__ VC4_SCALING_PPF ; 
 struct drm_gem_cma_object* drm_fb_cma_get_gem_obj (struct drm_framebuffer*,int /*<<< orphan*/ ) ; 
 int drm_format_horz_chroma_subsampling (int) ; 
 int drm_format_vert_chroma_subsampling (int) ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 
 void* vc4_get_scaling_mode (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vc4_plane_setup_clipping_and_scaling(struct drm_plane_state *state)
{
	struct drm_plane *plane = state->plane;
	struct vc4_plane_state *vc4_state = to_vc4_plane_state(state);
	struct drm_framebuffer *fb = state->fb;
	struct drm_gem_cma_object *bo = drm_fb_cma_get_gem_obj(fb, 0);
	u32 subpixel_src_mask = (1 << 16) - 1;
	u32 format = fb->format->format;
	int num_planes = fb->format->num_planes;
	u32 h_subsample = 1;
	u32 v_subsample = 1;
	int i;

	for (i = 0; i < num_planes; i++)
		vc4_state->offsets[i] = bo->paddr + fb->offsets[i];

	/* We don't support subpixel source positioning for scaling. */
	if ((state->src_x & subpixel_src_mask) ||
	    (state->src_y & subpixel_src_mask) ||
	    (state->src_w & subpixel_src_mask) ||
	    (state->src_h & subpixel_src_mask)) {
		return -EINVAL;
	}

	vc4_state->src_x = state->src_x >> 16;
	vc4_state->src_y = state->src_y >> 16;
	vc4_state->src_w[0] = state->src_w >> 16;
	vc4_state->src_h[0] = state->src_h >> 16;

	vc4_state->crtc_x = state->crtc_x;
	vc4_state->crtc_y = state->crtc_y;
	vc4_state->crtc_w = state->crtc_w;
	vc4_state->crtc_h = state->crtc_h;

	vc4_state->x_scaling[0] = vc4_get_scaling_mode(vc4_state->src_w[0],
						       vc4_state->crtc_w);
	vc4_state->y_scaling[0] = vc4_get_scaling_mode(vc4_state->src_h[0],
						       vc4_state->crtc_h);

	vc4_state->is_unity = (vc4_state->x_scaling[0] == VC4_SCALING_NONE &&
			       vc4_state->y_scaling[0] == VC4_SCALING_NONE);

	if (num_planes > 1) {
		vc4_state->is_yuv = true;

		h_subsample = drm_format_horz_chroma_subsampling(format);
		v_subsample = drm_format_vert_chroma_subsampling(format);
		vc4_state->src_w[1] = vc4_state->src_w[0] / h_subsample;
		vc4_state->src_h[1] = vc4_state->src_h[0] / v_subsample;

		vc4_state->x_scaling[1] =
			vc4_get_scaling_mode(vc4_state->src_w[1],
					     vc4_state->crtc_w);
		vc4_state->y_scaling[1] =
			vc4_get_scaling_mode(vc4_state->src_h[1],
					     vc4_state->crtc_h);

		/* YUV conversion requires that horizontal scaling be enabled
		 * on the UV plane even if vc4_get_scaling_mode() returned
		 * VC4_SCALING_NONE (which can happen when the down-scaling
		 * ratio is 0.5). Let's force it to VC4_SCALING_PPF in this
		 * case.
		 */
		if (vc4_state->x_scaling[1] == VC4_SCALING_NONE)
			vc4_state->x_scaling[1] = VC4_SCALING_PPF;
	} else {
		vc4_state->is_yuv = false;
		vc4_state->x_scaling[1] = VC4_SCALING_NONE;
		vc4_state->y_scaling[1] = VC4_SCALING_NONE;
	}

	/* No configuring scaling on the cursor plane, since it gets
	   non-vblank-synced updates, and scaling requires requires
	   LBM changes which have to be vblank-synced.
	 */
	if (plane->type == DRM_PLANE_TYPE_CURSOR && !vc4_state->is_unity)
		return -EINVAL;

	/* Clamp the on-screen start x/y to 0.  The hardware doesn't
	 * support negative y, and negative x wastes bandwidth.
	 */
	if (vc4_state->crtc_x < 0) {
		for (i = 0; i < num_planes; i++) {
			u32 cpp = fb->format->cpp[i];
			u32 subs = ((i == 0) ? 1 : h_subsample);

			vc4_state->offsets[i] += (cpp *
						  (-vc4_state->crtc_x) / subs);
		}
		vc4_state->src_w[0] += vc4_state->crtc_x;
		vc4_state->src_w[1] += vc4_state->crtc_x / h_subsample;
		vc4_state->crtc_x = 0;
	}

	if (vc4_state->crtc_y < 0) {
		for (i = 0; i < num_planes; i++) {
			u32 subs = ((i == 0) ? 1 : v_subsample);

			vc4_state->offsets[i] += (fb->pitches[i] *
						  (-vc4_state->crtc_y) / subs);
		}
		vc4_state->src_h[0] += vc4_state->crtc_y;
		vc4_state->src_h[1] += vc4_state->crtc_y / v_subsample;
		vc4_state->crtc_y = 0;
	}

	return 0;
}