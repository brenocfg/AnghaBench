#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct pixel_ext {int /*<<< orphan*/  bottom; int /*<<< orphan*/  top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; TYPE_2__ member_0; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_0; } ;
struct phase_step {int /*<<< orphan*/  y; int /*<<< orphan*/  x; TYPE_1__ member_0; } ;
struct TYPE_11__ {scalar_t__ pixel_format; } ;
struct mdp_format {TYPE_4__ base; } ;
struct mdp5_kms {int dummy; } ;
struct mdp5_hw_pipe {int pipe; int caps; } ;
struct drm_rect {scalar_t__ x1; scalar_t__ y1; } ;
struct drm_plane_state {int /*<<< orphan*/  rotation; } ;
struct drm_plane {int /*<<< orphan*/  name; struct drm_plane_state* state; } ;
struct TYPE_12__ {int /*<<< orphan*/  id; } ;
struct drm_framebuffer {TYPE_5__ base; int /*<<< orphan*/  height; int /*<<< orphan*/  width; TYPE_3__* format; } ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
struct drm_crtc {TYPE_6__ base; } ;
typedef  enum mdp5_pipe { ____Placeholder_mdp5_pipe } mdp5_pipe ;
struct TYPE_14__ {struct mdp5_hw_pipe* r_hwpipe; struct mdp5_hw_pipe* hwpipe; } ;
struct TYPE_10__ {scalar_t__ num_planes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__,...) ; 
 unsigned int DRM_MODE_REFLECT_X ; 
 unsigned int DRM_MODE_REFLECT_Y ; 
 unsigned int DRM_MODE_ROTATE_0 ; 
 int EINVAL ; 
 int MDP_PIPE_CAP_SW_PIX_EXT ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  calc_pixel_ext (struct mdp_format const*,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int calc_scalex_steps (struct drm_plane*,scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 int calc_scaley_steps (struct drm_plane*,scalar_t__,scalar_t__,unsigned int,int /*<<< orphan*/ ) ; 
 void* drm_rect_height (struct drm_rect*) ; 
 void* drm_rect_width (struct drm_rect*) ; 
 unsigned int drm_rotation_simplify (int /*<<< orphan*/ ,unsigned int) ; 
 struct mdp5_kms* get_kms (struct drm_plane*) ; 
 scalar_t__ get_scale_config (struct mdp_format const*,scalar_t__,unsigned int,int) ; 
 int /*<<< orphan*/  mdp5_hwpipe_mode_set (struct mdp5_kms*,struct mdp5_hw_pipe*,struct drm_framebuffer*,struct phase_step*,struct pixel_ext*,scalar_t__,scalar_t__,scalar_t__,int,int,int,int,unsigned int,unsigned int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  msm_framebuffer_format (struct drm_framebuffer*) ; 
 scalar_t__ pipe2nclients (int) ; 
 TYPE_7__* to_mdp5_plane_state (struct drm_plane_state*) ; 
 struct mdp_format* to_mdp_format (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mdp5_plane_mode_set(struct drm_plane *plane,
		struct drm_crtc *crtc, struct drm_framebuffer *fb,
		struct drm_rect *src, struct drm_rect *dest)
{
	struct drm_plane_state *pstate = plane->state;
	struct mdp5_hw_pipe *hwpipe = to_mdp5_plane_state(pstate)->hwpipe;
	struct mdp5_kms *mdp5_kms = get_kms(plane);
	enum mdp5_pipe pipe = hwpipe->pipe;
	struct mdp5_hw_pipe *right_hwpipe;
	const struct mdp_format *format;
	uint32_t nplanes, config = 0;
	struct phase_step step = { { 0 } };
	struct pixel_ext pe = { { 0 } };
	uint32_t hdecm = 0, vdecm = 0;
	uint32_t pix_format;
	unsigned int rotation;
	bool vflip, hflip;
	int crtc_x, crtc_y;
	unsigned int crtc_w, crtc_h;
	uint32_t src_x, src_y;
	uint32_t src_w, src_h;
	uint32_t src_img_w, src_img_h;
	int ret;

	nplanes = fb->format->num_planes;

	/* bad formats should already be rejected: */
	if (WARN_ON(nplanes > pipe2nclients(pipe)))
		return -EINVAL;

	format = to_mdp_format(msm_framebuffer_format(fb));
	pix_format = format->base.pixel_format;

	src_x = src->x1;
	src_y = src->y1;
	src_w = drm_rect_width(src);
	src_h = drm_rect_height(src);

	crtc_x = dest->x1;
	crtc_y = dest->y1;
	crtc_w = drm_rect_width(dest);
	crtc_h = drm_rect_height(dest);

	/* src values are in Q16 fixed point, convert to integer: */
	src_x = src_x >> 16;
	src_y = src_y >> 16;
	src_w = src_w >> 16;
	src_h = src_h >> 16;

	src_img_w = min(fb->width, src_w);
	src_img_h = min(fb->height, src_h);

	DBG("%s: FB[%u] %u,%u,%u,%u -> CRTC[%u] %d,%d,%u,%u", plane->name,
			fb->base.id, src_x, src_y, src_w, src_h,
			crtc->base.id, crtc_x, crtc_y, crtc_w, crtc_h);

	right_hwpipe = to_mdp5_plane_state(pstate)->r_hwpipe;
	if (right_hwpipe) {
		/*
		 * if the plane comprises of 2 hw pipes, assume that the width
		 * is split equally across them. The only parameters that varies
		 * between the 2 pipes are src_x and crtc_x
		 */
		crtc_w /= 2;
		src_w /= 2;
		src_img_w /= 2;
	}

	ret = calc_scalex_steps(plane, pix_format, src_w, crtc_w, step.x);
	if (ret)
		return ret;

	ret = calc_scaley_steps(plane, pix_format, src_h, crtc_h, step.y);
	if (ret)
		return ret;

	if (hwpipe->caps & MDP_PIPE_CAP_SW_PIX_EXT) {
		calc_pixel_ext(format, src_w, crtc_w, step.x,
			       pe.left, pe.right, true);
		calc_pixel_ext(format, src_h, crtc_h, step.y,
			       pe.top, pe.bottom, false);
	}

	/* TODO calc hdecm, vdecm */

	/* SCALE is used to both scale and up-sample chroma components */
	config |= get_scale_config(format, src_w, crtc_w, true);
	config |= get_scale_config(format, src_h, crtc_h, false);
	DBG("scale config = %x", config);

	rotation = drm_rotation_simplify(pstate->rotation,
					 DRM_MODE_ROTATE_0 |
					 DRM_MODE_REFLECT_X |
					 DRM_MODE_REFLECT_Y);
	hflip = !!(rotation & DRM_MODE_REFLECT_X);
	vflip = !!(rotation & DRM_MODE_REFLECT_Y);

	mdp5_hwpipe_mode_set(mdp5_kms, hwpipe, fb, &step, &pe,
			     config, hdecm, vdecm, hflip, vflip,
			     crtc_x, crtc_y, crtc_w, crtc_h,
			     src_img_w, src_img_h,
			     src_x, src_y, src_w, src_h);
	if (right_hwpipe)
		mdp5_hwpipe_mode_set(mdp5_kms, right_hwpipe, fb, &step, &pe,
				     config, hdecm, vdecm, hflip, vflip,
				     crtc_x + crtc_w, crtc_y, crtc_w, crtc_h,
				     src_img_w, src_img_h,
				     src_x + src_w, src_y, src_w, src_h);

	return ret;
}