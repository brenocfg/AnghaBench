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
typedef  int uint64_t ;
struct drm_property {int dummy; } ;
struct drm_plane_state {int crtc_w; int crtc_h; int src_x; int src_y; int src_w; int src_h; int alpha; int rotation; int zpos; int color_encoding; int color_range; int /*<<< orphan*/  crtc_y; int /*<<< orphan*/  crtc_x; TYPE_4__* crtc; TYPE_2__* fb; } ;
struct drm_plane {TYPE_5__* funcs; struct drm_property* color_range_property; struct drm_property* color_encoding_property; struct drm_property* zpos_property; struct drm_property* rotation_property; struct drm_property* alpha_property; struct drm_device* dev; } ;
struct drm_mode_config {struct drm_property* prop_src_h; struct drm_property* prop_src_w; struct drm_property* prop_src_y; struct drm_property* prop_src_x; struct drm_property* prop_crtc_h; struct drm_property* prop_crtc_w; struct drm_property* prop_crtc_y; struct drm_property* prop_crtc_x; struct drm_property* prop_crtc_id; struct drm_property* prop_in_fence_fd; struct drm_property* prop_fb_id; } ;
struct drm_device {struct drm_mode_config mode_config; } ;
struct TYPE_10__ {int (* atomic_get_property ) (struct drm_plane*,struct drm_plane_state const*,struct drm_property*,int*) ;} ;
struct TYPE_8__ {int id; } ;
struct TYPE_9__ {TYPE_3__ base; } ;
struct TYPE_6__ {int id; } ;
struct TYPE_7__ {TYPE_1__ base; } ;

/* Variables and functions */
 int EINVAL ; 
 int I642U64 (int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_plane*,struct drm_plane_state const*,struct drm_property*,int*) ; 

__attribute__((used)) static int
drm_atomic_plane_get_property(struct drm_plane *plane,
		const struct drm_plane_state *state,
		struct drm_property *property, uint64_t *val)
{
	struct drm_device *dev = plane->dev;
	struct drm_mode_config *config = &dev->mode_config;

	if (property == config->prop_fb_id) {
		*val = (state->fb) ? state->fb->base.id : 0;
	} else if (property == config->prop_in_fence_fd) {
		*val = -1;
	} else if (property == config->prop_crtc_id) {
		*val = (state->crtc) ? state->crtc->base.id : 0;
	} else if (property == config->prop_crtc_x) {
		*val = I642U64(state->crtc_x);
	} else if (property == config->prop_crtc_y) {
		*val = I642U64(state->crtc_y);
	} else if (property == config->prop_crtc_w) {
		*val = state->crtc_w;
	} else if (property == config->prop_crtc_h) {
		*val = state->crtc_h;
	} else if (property == config->prop_src_x) {
		*val = state->src_x;
	} else if (property == config->prop_src_y) {
		*val = state->src_y;
	} else if (property == config->prop_src_w) {
		*val = state->src_w;
	} else if (property == config->prop_src_h) {
		*val = state->src_h;
	} else if (property == plane->alpha_property) {
		*val = state->alpha;
	} else if (property == plane->rotation_property) {
		*val = state->rotation;
	} else if (property == plane->zpos_property) {
		*val = state->zpos;
	} else if (property == plane->color_encoding_property) {
		*val = state->color_encoding;
	} else if (property == plane->color_range_property) {
		*val = state->color_range;
	} else if (plane->funcs->atomic_get_property) {
		return plane->funcs->atomic_get_property(plane, state, property, val);
	} else {
		return -EINVAL;
	}

	return 0;
}