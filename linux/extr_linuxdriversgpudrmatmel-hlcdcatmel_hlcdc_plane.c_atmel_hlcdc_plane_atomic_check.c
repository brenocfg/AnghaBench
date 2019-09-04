#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct drm_plane_state {int src_x; int src_y; int src_h; int src_w; unsigned int crtc_x; unsigned int crtc_y; unsigned int crtc_h; unsigned int crtc_w; int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int* pitches; TYPE_3__* format; scalar_t__* offsets; } ;
struct drm_display_mode {unsigned int hdisplay; unsigned int vdisplay; } ;
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct TYPE_8__ {int rotation; struct drm_framebuffer* fb; int /*<<< orphan*/  crtc; } ;
struct atmel_hlcdc_plane_state {int src_x; int src_y; int src_h; int src_w; unsigned int crtc_x; unsigned int crtc_y; unsigned int crtc_h; unsigned int crtc_w; int nplanes; int* bpp; unsigned int* xstride; unsigned int* pstride; TYPE_4__ base; scalar_t__* offsets; } ;
struct TYPE_5__ {struct atmel_hlcdc_layer_desc* desc; } ;
struct atmel_hlcdc_plane {TYPE_1__ layer; } ;
struct TYPE_6__ {int /*<<< orphan*/  memsize; int /*<<< orphan*/  size; } ;
struct atmel_hlcdc_layer_desc {unsigned int max_height; unsigned int max_width; TYPE_2__ layout; } ;
struct TYPE_7__ {int num_planes; int* cpp; scalar_t__ has_alpha; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int ATMEL_HLCDC_LAYER_MAX_PLANES ; 
 unsigned int DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 int DRM_MODE_ROTATE_MASK ; 
 int EINVAL ; 
 int SUBPIXEL_MASK ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_format_horz_chroma_subsampling (int /*<<< orphan*/ ) ; 
 int drm_format_vert_chroma_subsampling (int /*<<< orphan*/ ) ; 
 struct atmel_hlcdc_plane_state* drm_plane_state_to_atmel_hlcdc_plane_state (struct drm_plane_state*) ; 
 struct atmel_hlcdc_plane* drm_plane_to_atmel_hlcdc_plane (struct drm_plane*) ; 
 scalar_t__ drm_rotation_90_or_270 (int) ; 

__attribute__((used)) static int atmel_hlcdc_plane_atomic_check(struct drm_plane *p,
					  struct drm_plane_state *s)
{
	struct atmel_hlcdc_plane *plane = drm_plane_to_atmel_hlcdc_plane(p);
	struct atmel_hlcdc_plane_state *state =
				drm_plane_state_to_atmel_hlcdc_plane_state(s);
	const struct atmel_hlcdc_layer_desc *desc = plane->layer.desc;
	struct drm_framebuffer *fb = state->base.fb;
	const struct drm_display_mode *mode;
	struct drm_crtc_state *crtc_state;
	unsigned int patched_crtc_w;
	unsigned int patched_crtc_h;
	unsigned int patched_src_w;
	unsigned int patched_src_h;
	unsigned int tmp;
	int x_offset = 0;
	int y_offset = 0;
	int hsub = 1;
	int vsub = 1;
	int i;

	if (!state->base.crtc || !fb)
		return 0;

	crtc_state = drm_atomic_get_existing_crtc_state(s->state, s->crtc);
	mode = &crtc_state->adjusted_mode;

	state->src_x = s->src_x;
	state->src_y = s->src_y;
	state->src_h = s->src_h;
	state->src_w = s->src_w;
	state->crtc_x = s->crtc_x;
	state->crtc_y = s->crtc_y;
	state->crtc_h = s->crtc_h;
	state->crtc_w = s->crtc_w;
	if ((state->src_x | state->src_y | state->src_w | state->src_h) &
	    SUBPIXEL_MASK)
		return -EINVAL;

	state->src_x >>= 16;
	state->src_y >>= 16;
	state->src_w >>= 16;
	state->src_h >>= 16;

	state->nplanes = fb->format->num_planes;
	if (state->nplanes > ATMEL_HLCDC_LAYER_MAX_PLANES)
		return -EINVAL;

	/*
	 * Swap width and size in case of 90 or 270 degrees rotation
	 */
	if (drm_rotation_90_or_270(state->base.rotation)) {
		tmp = state->crtc_w;
		state->crtc_w = state->crtc_h;
		state->crtc_h = tmp;
		tmp = state->src_w;
		state->src_w = state->src_h;
		state->src_h = tmp;
	}

	if (state->crtc_x + state->crtc_w > mode->hdisplay)
		patched_crtc_w = mode->hdisplay - state->crtc_x;
	else
		patched_crtc_w = state->crtc_w;

	if (state->crtc_x < 0) {
		patched_crtc_w += state->crtc_x;
		x_offset = -state->crtc_x;
		state->crtc_x = 0;
	}

	if (state->crtc_y + state->crtc_h > mode->vdisplay)
		patched_crtc_h = mode->vdisplay - state->crtc_y;
	else
		patched_crtc_h = state->crtc_h;

	if (state->crtc_y < 0) {
		patched_crtc_h += state->crtc_y;
		y_offset = -state->crtc_y;
		state->crtc_y = 0;
	}

	patched_src_w = DIV_ROUND_CLOSEST(patched_crtc_w * state->src_w,
					  state->crtc_w);
	patched_src_h = DIV_ROUND_CLOSEST(patched_crtc_h * state->src_h,
					  state->crtc_h);

	hsub = drm_format_horz_chroma_subsampling(fb->format->format);
	vsub = drm_format_vert_chroma_subsampling(fb->format->format);

	for (i = 0; i < state->nplanes; i++) {
		unsigned int offset = 0;
		int xdiv = i ? hsub : 1;
		int ydiv = i ? vsub : 1;

		state->bpp[i] = fb->format->cpp[i];
		if (!state->bpp[i])
			return -EINVAL;

		switch (state->base.rotation & DRM_MODE_ROTATE_MASK) {
		case DRM_MODE_ROTATE_90:
			offset = ((y_offset + state->src_y + patched_src_w - 1) /
				  ydiv) * fb->pitches[i];
			offset += ((x_offset + state->src_x) / xdiv) *
				  state->bpp[i];
			state->xstride[i] = ((patched_src_w - 1) / ydiv) *
					  fb->pitches[i];
			state->pstride[i] = -fb->pitches[i] - state->bpp[i];
			break;
		case DRM_MODE_ROTATE_180:
			offset = ((y_offset + state->src_y + patched_src_h - 1) /
				  ydiv) * fb->pitches[i];
			offset += ((x_offset + state->src_x + patched_src_w - 1) /
				   xdiv) * state->bpp[i];
			state->xstride[i] = ((((patched_src_w - 1) / xdiv) - 1) *
					   state->bpp[i]) - fb->pitches[i];
			state->pstride[i] = -2 * state->bpp[i];
			break;
		case DRM_MODE_ROTATE_270:
			offset = ((y_offset + state->src_y) / ydiv) *
				 fb->pitches[i];
			offset += ((x_offset + state->src_x + patched_src_h - 1) /
				   xdiv) * state->bpp[i];
			state->xstride[i] = -(((patched_src_w - 1) / ydiv) *
					    fb->pitches[i]) -
					  (2 * state->bpp[i]);
			state->pstride[i] = fb->pitches[i] - state->bpp[i];
			break;
		case DRM_MODE_ROTATE_0:
		default:
			offset = ((y_offset + state->src_y) / ydiv) *
				 fb->pitches[i];
			offset += ((x_offset + state->src_x) / xdiv) *
				  state->bpp[i];
			state->xstride[i] = fb->pitches[i] -
					  ((patched_src_w / xdiv) *
					   state->bpp[i]);
			state->pstride[i] = 0;
			break;
		}

		state->offsets[i] = offset + fb->offsets[i];
	}

	state->src_w = patched_src_w;
	state->src_h = patched_src_h;
	state->crtc_w = patched_crtc_w;
	state->crtc_h = patched_crtc_h;

	if (!desc->layout.size &&
	    (mode->hdisplay != state->crtc_w ||
	     mode->vdisplay != state->crtc_h))
		return -EINVAL;

	if (desc->max_height && state->crtc_h > desc->max_height)
		return -EINVAL;

	if (desc->max_width && state->crtc_w > desc->max_width)
		return -EINVAL;

	if ((state->crtc_h != state->src_h || state->crtc_w != state->src_w) &&
	    (!desc->layout.memsize ||
	     state->base.fb->format->has_alpha))
		return -EINVAL;

	if (state->crtc_x < 0 || state->crtc_y < 0)
		return -EINVAL;

	if (state->crtc_w + state->crtc_x > mode->hdisplay ||
	    state->crtc_h + state->crtc_y > mode->vdisplay)
		return -EINVAL;

	return 0;
}