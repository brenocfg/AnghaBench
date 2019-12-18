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
struct komeda_data_flow_cfg {int layer_alpha; scalar_t__ blending_zorder; int /*<<< orphan*/  pixel_blend_mode; int /*<<< orphan*/  in_h; int /*<<< orphan*/  out_h; int /*<<< orphan*/  in_w; int /*<<< orphan*/  out_w; int /*<<< orphan*/  input; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct komeda_crtc_state {TYPE_1__ base; } ;
struct komeda_component_state {int dummy; } ;
struct komeda_compiz_state {int /*<<< orphan*/  vsize; int /*<<< orphan*/  hsize; } ;
struct komeda_compiz {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_BLEND_PIXEL_NONE ; 
 scalar_t__ IS_ERR (struct komeda_component_state*) ; 
 int PTR_ERR (struct komeda_component_state*) ; 
 struct komeda_component_state* komeda_component_get_state_and_set_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_component_set_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipeline_composition_size (struct komeda_crtc_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct komeda_compiz_state* to_compiz_st (struct komeda_component_state*) ; 

__attribute__((used)) static int
komeda_compiz_validate(struct komeda_compiz *compiz,
		       struct komeda_crtc_state *state,
		       struct komeda_data_flow_cfg *dflow)
{
	struct komeda_component_state *c_st;
	struct komeda_compiz_state *st;

	c_st = komeda_component_get_state_and_set_user(&compiz->base,
			state->base.state, state->base.crtc, state->base.crtc);
	if (IS_ERR(c_st))
		return PTR_ERR(c_st);

	st = to_compiz_st(c_st);

	pipeline_composition_size(state, &st->hsize, &st->vsize);

	komeda_component_set_output(&dflow->input, &compiz->base, 0);

	/* compiz output dflow will be fed to the next pipeline stage, prepare
	 * the data flow configuration for the next stage
	 */
	if (dflow) {
		dflow->in_w = st->hsize;
		dflow->in_h = st->vsize;
		dflow->out_w = dflow->in_w;
		dflow->out_h = dflow->in_h;
		/* the output data of compiz doesn't have alpha, it only can be
		 * used as bottom layer when blend it with master layers
		 */
		dflow->pixel_blend_mode = DRM_MODE_BLEND_PIXEL_NONE;
		dflow->layer_alpha = 0xFF;
		dflow->blending_zorder = 0;
	}

	return 0;
}