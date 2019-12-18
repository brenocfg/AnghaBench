#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct komeda_plane {TYPE_5__* layer; } ;
struct komeda_pipeline {int dummy; } ;
struct komeda_format_caps {int /*<<< orphan*/  fourcc; int /*<<< orphan*/  supported_rots; } ;
struct komeda_data_flow_cfg {scalar_t__ blending_zorder; int layer_alpha; int in_x; int in_y; int in_w; int in_h; int /*<<< orphan*/  rot; int /*<<< orphan*/  out_h; int /*<<< orphan*/  out_w; int /*<<< orphan*/  out_y; int /*<<< orphan*/  out_x; int /*<<< orphan*/  pixel_blend_mode; } ;
struct komeda_crtc_state {scalar_t__ max_slave_zorder; } ;
struct drm_plane_state {scalar_t__ normalized_zpos; int alpha; int src_x; int src_y; int src_w; int src_h; int /*<<< orphan*/  rotation; int /*<<< orphan*/  crtc_h; int /*<<< orphan*/  crtc_w; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; int /*<<< orphan*/  pixel_blend_mode; TYPE_2__* plane; int /*<<< orphan*/  crtc; struct drm_framebuffer* fb; } ;
struct drm_framebuffer {int /*<<< orphan*/  modifier; } ;
struct TYPE_6__ {struct komeda_pipeline* pipeline; } ;
struct TYPE_10__ {TYPE_1__ base; } ;
struct TYPE_9__ {struct komeda_pipeline* master; } ;
struct TYPE_8__ {struct komeda_format_caps* format_caps; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  drm_rotation_simplify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_complete_data_flow_cfg (TYPE_5__*,struct komeda_data_flow_cfg*,struct drm_framebuffer*) ; 
 int /*<<< orphan*/  komeda_get_format_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct komeda_data_flow_cfg*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* to_kcrtc (int /*<<< orphan*/ ) ; 
 TYPE_3__* to_kfb (struct drm_framebuffer*) ; 
 struct komeda_plane* to_kplane (TYPE_2__*) ; 

__attribute__((used)) static int
komeda_plane_init_data_flow(struct drm_plane_state *st,
			    struct komeda_crtc_state *kcrtc_st,
			    struct komeda_data_flow_cfg *dflow)
{
	struct komeda_plane *kplane = to_kplane(st->plane);
	struct drm_framebuffer *fb = st->fb;
	const struct komeda_format_caps *caps = to_kfb(fb)->format_caps;
	struct komeda_pipeline *pipe = kplane->layer->base.pipeline;

	memset(dflow, 0, sizeof(*dflow));

	dflow->blending_zorder = st->normalized_zpos;
	if (pipe == to_kcrtc(st->crtc)->master)
		dflow->blending_zorder -= kcrtc_st->max_slave_zorder;
	if (dflow->blending_zorder < 0) {
		DRM_DEBUG_ATOMIC("%s zorder:%d < max_slave_zorder: %d.\n",
				 st->plane->name, st->normalized_zpos,
				 kcrtc_st->max_slave_zorder);
		return -EINVAL;
	}

	dflow->pixel_blend_mode = st->pixel_blend_mode;
	dflow->layer_alpha = st->alpha >> 8;

	dflow->out_x = st->crtc_x;
	dflow->out_y = st->crtc_y;
	dflow->out_w = st->crtc_w;
	dflow->out_h = st->crtc_h;

	dflow->in_x = st->src_x >> 16;
	dflow->in_y = st->src_y >> 16;
	dflow->in_w = st->src_w >> 16;
	dflow->in_h = st->src_h >> 16;

	dflow->rot = drm_rotation_simplify(st->rotation, caps->supported_rots);
	if (!has_bits(dflow->rot, caps->supported_rots)) {
		DRM_DEBUG_ATOMIC("rotation(0x%x) isn't supported by %s.\n",
				 dflow->rot,
				 komeda_get_format_name(caps->fourcc,
							fb->modifier));
		return -EINVAL;
	}

	komeda_complete_data_flow_cfg(kplane->layer, dflow, fb);

	return 0;
}