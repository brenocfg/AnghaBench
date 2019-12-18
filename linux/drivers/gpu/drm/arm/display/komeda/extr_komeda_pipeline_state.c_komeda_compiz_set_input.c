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
typedef  scalar_t__ u16 ;
struct komeda_data_flow_cfg {int blending_zorder; scalar_t__ out_x; scalar_t__ out_w; scalar_t__ out_y; scalar_t__ out_h; int /*<<< orphan*/  input; int /*<<< orphan*/  layer_alpha; int /*<<< orphan*/  pixel_blend_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  crtc; struct drm_atomic_state* state; } ;
struct komeda_crtc_state {TYPE_1__ base; } ;
struct komeda_component_state {int /*<<< orphan*/  changed_active_inputs; } ;
struct komeda_compiz_input_cfg {scalar_t__ hsize; scalar_t__ vsize; scalar_t__ hoffset; scalar_t__ voffset; int /*<<< orphan*/  layer_alpha; int /*<<< orphan*/  pixel_blend_mode; } ;
struct komeda_compiz {int /*<<< orphan*/  base; } ;
struct drm_atomic_state {int dummy; } ;
struct TYPE_4__ {struct komeda_compiz_input_cfg* cins; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct komeda_component_state*) ; 
 int PTR_ERR (struct komeda_component_state*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  komeda_component_add_input (struct komeda_component_state*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ komeda_component_check_input (struct komeda_component_state*,int /*<<< orphan*/ *,int) ; 
 struct komeda_component_state* komeda_component_get_old_state (int /*<<< orphan*/ *,struct drm_atomic_state*) ; 
 struct komeda_component_state* komeda_component_get_state_and_set_user (int /*<<< orphan*/ *,struct drm_atomic_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_component_set_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct komeda_compiz_input_cfg*,struct komeda_compiz_input_cfg*,int) ; 
 int /*<<< orphan*/  pipeline_composition_size (struct komeda_crtc_state*,scalar_t__*,scalar_t__*) ; 
 TYPE_2__* to_compiz_st (struct komeda_component_state*) ; 

__attribute__((used)) static int
komeda_compiz_set_input(struct komeda_compiz *compiz,
			struct komeda_crtc_state *kcrtc_st,
			struct komeda_data_flow_cfg *dflow)
{
	struct drm_atomic_state *drm_st = kcrtc_st->base.state;
	struct komeda_component_state *c_st, *old_st;
	struct komeda_compiz_input_cfg *cin;
	u16 compiz_w, compiz_h;
	int idx = dflow->blending_zorder;

	pipeline_composition_size(kcrtc_st, &compiz_w, &compiz_h);
	/* check display rect */
	if ((dflow->out_x + dflow->out_w > compiz_w) ||
	    (dflow->out_y + dflow->out_h > compiz_h) ||
	     dflow->out_w == 0 || dflow->out_h == 0) {
		DRM_DEBUG_ATOMIC("invalid disp rect [x=%d, y=%d, w=%d, h=%d]\n",
				 dflow->out_x, dflow->out_y,
				 dflow->out_w, dflow->out_h);
		return -EINVAL;
	}

	c_st = komeda_component_get_state_and_set_user(&compiz->base, drm_st,
			kcrtc_st->base.crtc, kcrtc_st->base.crtc);
	if (IS_ERR(c_st))
		return PTR_ERR(c_st);

	if (komeda_component_check_input(c_st, &dflow->input, idx))
		return -EINVAL;

	cin = &(to_compiz_st(c_st)->cins[idx]);

	cin->hsize   = dflow->out_w;
	cin->vsize   = dflow->out_h;
	cin->hoffset = dflow->out_x;
	cin->voffset = dflow->out_y;
	cin->pixel_blend_mode = dflow->pixel_blend_mode;
	cin->layer_alpha = dflow->layer_alpha;

	old_st = komeda_component_get_old_state(&compiz->base, drm_st);
	WARN_ON(!old_st);

	/* compare with old to check if this input has been changed */
	if (memcmp(&(to_compiz_st(old_st)->cins[idx]), cin, sizeof(*cin)))
		c_st->changed_active_inputs |= BIT(idx);

	komeda_component_add_input(c_st, &dflow->input, idx);
	komeda_component_set_output(&dflow->input, &compiz->base, 0);

	return 0;
}