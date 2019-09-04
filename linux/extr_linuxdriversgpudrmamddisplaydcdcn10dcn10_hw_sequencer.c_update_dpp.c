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
struct dpp {TYPE_1__* funcs; } ;
struct dc_plane_state {int /*<<< orphan*/  input_csc_color_matrix; int /*<<< orphan*/  format; } ;
struct dc_bias_and_scale {int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dpp_program_bias_and_scale ) (struct dpp*,struct dc_bias_and_scale*) ;int /*<<< orphan*/  (* dpp_setup ) (struct dpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_SPACE_YCBCR601_LIMITED ; 
 int /*<<< orphan*/  EXPANSION_MODE_ZERO ; 
 int /*<<< orphan*/  build_prescale_params (struct dc_bias_and_scale*,struct dc_plane_state*) ; 
 int /*<<< orphan*/  stub1 (struct dpp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct dpp*,struct dc_bias_and_scale*) ; 

__attribute__((used)) static void update_dpp(struct dpp *dpp, struct dc_plane_state *plane_state)
{
	struct dc_bias_and_scale bns_params = {0};

	// program the input csc
	dpp->funcs->dpp_setup(dpp,
			plane_state->format,
			EXPANSION_MODE_ZERO,
			plane_state->input_csc_color_matrix,
			COLOR_SPACE_YCBCR601_LIMITED);

	//set scale and bias registers
	build_prescale_params(&bns_params, plane_state);
	if (dpp->funcs->dpp_program_bias_and_scale)
		dpp->funcs->dpp_program_bias_and_scale(dpp, &bns_params);
}