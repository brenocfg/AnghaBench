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
struct komeda_improc_state {int /*<<< orphan*/  base; int /*<<< orphan*/  vsize; int /*<<< orphan*/  hsize; } ;
struct komeda_improc {int /*<<< orphan*/  base; } ;
struct komeda_data_flow_cfg {int /*<<< orphan*/  input; int /*<<< orphan*/  in_h; int /*<<< orphan*/  in_w; } ;
struct TYPE_2__ {int /*<<< orphan*/  state; struct drm_crtc* crtc; } ;
struct komeda_crtc_state {TYPE_1__ base; } ;
struct komeda_component_state {int dummy; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct komeda_component_state*) ; 
 int PTR_ERR (struct komeda_component_state*) ; 
 int /*<<< orphan*/  komeda_component_add_input (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct komeda_component_state* komeda_component_get_state_and_set_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct drm_crtc*,struct drm_crtc*) ; 
 int /*<<< orphan*/  komeda_component_set_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct komeda_improc_state* to_improc_st (struct komeda_component_state*) ; 

__attribute__((used)) static int
komeda_improc_validate(struct komeda_improc *improc,
		       struct komeda_crtc_state *kcrtc_st,
		       struct komeda_data_flow_cfg *dflow)
{
	struct drm_crtc *crtc = kcrtc_st->base.crtc;
	struct komeda_component_state *c_st;
	struct komeda_improc_state *st;

	c_st = komeda_component_get_state_and_set_user(&improc->base,
			kcrtc_st->base.state, crtc, crtc);
	if (IS_ERR(c_st))
		return PTR_ERR(c_st);

	st = to_improc_st(c_st);

	st->hsize = dflow->in_w;
	st->vsize = dflow->in_h;

	komeda_component_add_input(&st->base, &dflow->input, 0);
	komeda_component_set_output(&dflow->input, &improc->base, 0);

	return 0;
}