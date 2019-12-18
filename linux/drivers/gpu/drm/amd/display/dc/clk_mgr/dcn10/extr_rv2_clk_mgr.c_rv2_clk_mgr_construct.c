#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pp_smu_funcs {int dummy; } ;
struct dc_context {int dummy; } ;
struct clk_mgr_internal {int /*<<< orphan*/ * funcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  rv1_clk_mgr_construct (struct dc_context*,struct clk_mgr_internal*,struct pp_smu_funcs*) ; 
 int /*<<< orphan*/  rv2_clk_internal_funcs ; 

void rv2_clk_mgr_construct(struct dc_context *ctx, struct clk_mgr_internal *clk_mgr, struct pp_smu_funcs *pp_smu)

{
	rv1_clk_mgr_construct(ctx, clk_mgr, pp_smu);

	clk_mgr->funcs = &rv2_clk_internal_funcs;
}