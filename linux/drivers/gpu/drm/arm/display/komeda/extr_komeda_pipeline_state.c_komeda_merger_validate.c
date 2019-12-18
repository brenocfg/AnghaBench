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
struct komeda_merger_state {int /*<<< orphan*/  vsize_merged; int /*<<< orphan*/  hsize_merged; } ;
struct komeda_merger {int /*<<< orphan*/  base; int /*<<< orphan*/  vsize_merged; int /*<<< orphan*/  hsize_merged; } ;
struct komeda_data_flow_cfg {int /*<<< orphan*/  input; int /*<<< orphan*/  out_h; int /*<<< orphan*/  out_w; } ;
struct TYPE_2__ {int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct komeda_crtc_state {TYPE_1__ base; } ;
struct komeda_component_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,...) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct komeda_component_state*) ; 
 int PTR_ERR (struct komeda_component_state*) ; 
 int /*<<< orphan*/  in_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_component_add_input (struct komeda_component_state*,int /*<<< orphan*/ *,int) ; 
 struct komeda_component_state* komeda_component_get_state_and_set_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  komeda_component_set_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct komeda_merger_state* to_merger_st (struct komeda_component_state*) ; 

__attribute__((used)) static int
komeda_merger_validate(struct komeda_merger *merger,
		       void *user,
		       struct komeda_crtc_state *kcrtc_st,
		       struct komeda_data_flow_cfg *left_input,
		       struct komeda_data_flow_cfg *right_input,
		       struct komeda_data_flow_cfg *output)
{
	struct komeda_component_state *c_st;
	struct komeda_merger_state *st;
	int err = 0;

	if (!merger) {
		DRM_DEBUG_ATOMIC("No merger is available");
		return -EINVAL;
	}

	if (!in_range(&merger->hsize_merged, output->out_w)) {
		DRM_DEBUG_ATOMIC("merged_w: %d is out of the accepted range.\n",
				 output->out_w);
		return -EINVAL;
	}

	if (!in_range(&merger->vsize_merged, output->out_h)) {
		DRM_DEBUG_ATOMIC("merged_h: %d is out of the accepted range.\n",
				 output->out_h);
		return -EINVAL;
	}

	c_st = komeda_component_get_state_and_set_user(&merger->base,
			kcrtc_st->base.state, kcrtc_st->base.crtc, kcrtc_st->base.crtc);

	if (IS_ERR(c_st))
		return PTR_ERR(c_st);

	st = to_merger_st(c_st);
	st->hsize_merged = output->out_w;
	st->vsize_merged = output->out_h;

	komeda_component_add_input(c_st, &left_input->input, 0);
	komeda_component_add_input(c_st, &right_input->input, 1);
	komeda_component_set_output(&output->input, &merger->base, 0);

	return err;
}