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
struct TYPE_5__ {struct drm_plane* plane; } ;
struct komeda_plane_state {TYPE_1__ base; } ;
struct komeda_pipeline {int /*<<< orphan*/  compiz; int /*<<< orphan*/  merger; int /*<<< orphan*/ * scalers; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; struct komeda_pipeline* pipeline; } ;
struct komeda_layer {TYPE_2__ base; struct komeda_layer* right; } ;
struct TYPE_8__ {scalar_t__ component; } ;
struct komeda_data_flow_cfg {TYPE_4__ input; int /*<<< orphan*/  rot; int /*<<< orphan*/  out_h; int /*<<< orphan*/  out_w; int /*<<< orphan*/  out_y; int /*<<< orphan*/  out_x; int /*<<< orphan*/  in_h; int /*<<< orphan*/  in_w; int /*<<< orphan*/  in_y; int /*<<< orphan*/  in_x; } ;
struct komeda_crtc_state {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int /*<<< orphan*/  name; TYPE_3__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int komeda_build_layer_data_flow (struct komeda_layer*,struct komeda_plane_state*,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int komeda_compiz_set_input (int /*<<< orphan*/ ,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int komeda_merger_validate (int /*<<< orphan*/ ,struct drm_plane*,struct komeda_crtc_state*,struct komeda_data_flow_cfg*,struct komeda_data_flow_cfg*,struct komeda_data_flow_cfg*) ; 
 int /*<<< orphan*/  komeda_rotate_data_flow (struct komeda_data_flow_cfg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_split_data_flow (int /*<<< orphan*/ ,struct komeda_data_flow_cfg*,struct komeda_data_flow_cfg*,struct komeda_data_flow_cfg*) ; 

int komeda_build_layer_split_data_flow(struct komeda_layer *left,
				       struct komeda_plane_state *kplane_st,
				       struct komeda_crtc_state *kcrtc_st,
				       struct komeda_data_flow_cfg *dflow)
{
	struct drm_plane *plane = kplane_st->base.plane;
	struct komeda_pipeline *pipe = left->base.pipeline;
	struct komeda_layer *right = left->right;
	struct komeda_data_flow_cfg l_dflow, r_dflow;
	int err;

	komeda_split_data_flow(pipe->scalers[0], dflow, &l_dflow, &r_dflow);

	DRM_DEBUG_ATOMIC("Assign %s + %s to [PLANE:%d:%s]: "
			 "src[x/y:%d/%d, w/h:%d/%d] disp[x/y:%d/%d, w/h:%d/%d]",
			 left->base.name, right->base.name,
			 plane->base.id, plane->name,
			 dflow->in_x, dflow->in_y, dflow->in_w, dflow->in_h,
			 dflow->out_x, dflow->out_y, dflow->out_w, dflow->out_h);

	err = komeda_build_layer_data_flow(left, kplane_st, kcrtc_st, &l_dflow);
	if (err)
		return err;

	err = komeda_build_layer_data_flow(right, kplane_st, kcrtc_st, &r_dflow);
	if (err)
		return err;

	/* The rotation has been handled by layer, so adjusted the data flow */
	komeda_rotate_data_flow(dflow, dflow->rot);

	/* left and right dflow has been merged to compiz already,
	 * no need merger to merge them anymore.
	 */
	if (r_dflow.input.component == l_dflow.input.component)
		return 0;

	/* line merger path */
	err = komeda_merger_validate(pipe->merger, plane, kcrtc_st,
				     &l_dflow, &r_dflow, dflow);
	if (err)
		return err;

	err = komeda_compiz_set_input(pipe->compiz, kcrtc_st, dflow);

	return err;
}