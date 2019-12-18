#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int x1; int y1; } ;
struct drm_plane_state {TYPE_5__ dst; TYPE_5__ src; int /*<<< orphan*/  visible; int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int* pitches; TYPE_4__* format; scalar_t__* offsets; } ;
struct drm_display_mode {int hdisplay; unsigned int vdisplay; } ;
struct drm_crtc_state {struct drm_display_mode adjusted_mode; } ;
struct TYPE_9__ {int rotation; struct drm_framebuffer* fb; int /*<<< orphan*/  crtc; } ;
struct atmel_hlcdc_plane_state {int src_x; int src_y; int src_w; int src_h; int crtc_x; int crtc_y; int crtc_w; unsigned int crtc_h; int nplanes; int* bpp; int* xstride; int* pstride; TYPE_3__ base; scalar_t__* offsets; } ;
struct TYPE_8__ {struct atmel_hlcdc_layer_desc* desc; } ;
struct atmel_hlcdc_plane {TYPE_2__ layer; } ;
struct TYPE_7__ {int /*<<< orphan*/  memsize; int /*<<< orphan*/  size; } ;
struct atmel_hlcdc_layer_desc {TYPE_1__ layout; } ;
struct TYPE_10__ {int num_planes; int hsub; int vsub; int* cpp; scalar_t__ has_alpha; } ;

/* Variables and functions */
 int ATMEL_HLCDC_LAYER_MAX_PLANES ; 
#define  DRM_MODE_ROTATE_0 131 
#define  DRM_MODE_ROTATE_180 130 
#define  DRM_MODE_ROTATE_270 129 
#define  DRM_MODE_ROTATE_90 128 
 int DRM_MODE_ROTATE_MASK ; 
 int EINVAL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int SUBPIXEL_MASK ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int,int /*<<< orphan*/ ,int,int) ; 
 struct atmel_hlcdc_plane_state* drm_plane_state_to_atmel_hlcdc_plane_state (struct drm_plane_state*) ; 
 struct atmel_hlcdc_plane* drm_plane_to_atmel_hlcdc_plane (struct drm_plane*) ; 
 void* drm_rect_height (TYPE_5__*) ; 
 void* drm_rect_width (TYPE_5__*) ; 
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
	unsigned int tmp;
	int ret;
	int i;

	if (!state->base.crtc || !fb)
		return 0;

	crtc_state = drm_atomic_get_existing_crtc_state(s->state, s->crtc);
	mode = &crtc_state->adjusted_mode;

	ret = drm_atomic_helper_check_plane_state(s, crtc_state,
						  (1 << 16) / 2048,
						  INT_MAX, true, true);
	if (ret || !s->visible)
		return ret;

	state->src_x = s->src.x1;
	state->src_y = s->src.y1;
	state->src_w = drm_rect_width(&s->src);
	state->src_h = drm_rect_height(&s->src);
	state->crtc_x = s->dst.x1;
	state->crtc_y = s->dst.y1;
	state->crtc_w = drm_rect_width(&s->dst);
	state->crtc_h = drm_rect_height(&s->dst);

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

	for (i = 0; i < state->nplanes; i++) {
		unsigned int offset = 0;
		int xdiv = i ? fb->format->hsub : 1;
		int ydiv = i ? fb->format->vsub : 1;

		state->bpp[i] = fb->format->cpp[i];
		if (!state->bpp[i])
			return -EINVAL;

		switch (state->base.rotation & DRM_MODE_ROTATE_MASK) {
		case DRM_MODE_ROTATE_90:
			offset = (state->src_y / ydiv) *
				 fb->pitches[i];
			offset += ((state->src_x + state->src_w - 1) /
				   xdiv) * state->bpp[i];
			state->xstride[i] = -(((state->src_h - 1) / ydiv) *
					    fb->pitches[i]) -
					  (2 * state->bpp[i]);
			state->pstride[i] = fb->pitches[i] - state->bpp[i];
			break;
		case DRM_MODE_ROTATE_180:
			offset = ((state->src_y + state->src_h - 1) /
				  ydiv) * fb->pitches[i];
			offset += ((state->src_x + state->src_w - 1) /
				   xdiv) * state->bpp[i];
			state->xstride[i] = ((((state->src_w - 1) / xdiv) - 1) *
					   state->bpp[i]) - fb->pitches[i];
			state->pstride[i] = -2 * state->bpp[i];
			break;
		case DRM_MODE_ROTATE_270:
			offset = ((state->src_y + state->src_h - 1) /
				  ydiv) * fb->pitches[i];
			offset += (state->src_x / xdiv) * state->bpp[i];
			state->xstride[i] = ((state->src_h - 1) / ydiv) *
					  fb->pitches[i];
			state->pstride[i] = -fb->pitches[i] - state->bpp[i];
			break;
		case DRM_MODE_ROTATE_0:
		default:
			offset = (state->src_y / ydiv) * fb->pitches[i];
			offset += (state->src_x / xdiv) * state->bpp[i];
			state->xstride[i] = fb->pitches[i] -
					  ((state->src_w / xdiv) *
					   state->bpp[i]);
			state->pstride[i] = 0;
			break;
		}

		state->offsets[i] = offset + fb->offsets[i];
	}

	/*
	 * Swap width and size in case of 90 or 270 degrees rotation
	 */
	if (drm_rotation_90_or_270(state->base.rotation)) {
		tmp = state->src_w;
		state->src_w = state->src_h;
		state->src_h = tmp;
	}

	if (!desc->layout.size &&
	    (mode->hdisplay != state->crtc_w ||
	     mode->vdisplay != state->crtc_h))
		return -EINVAL;

	if ((state->crtc_h != state->src_h || state->crtc_w != state->src_w) &&
	    (!desc->layout.memsize ||
	     state->base.fb->format->has_alpha))
		return -EINVAL;

	return 0;
}