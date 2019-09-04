#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct dmcu {TYPE_3__* funcs; } ;
struct TYPE_4__ {struct dc_context* ctx; } ;
struct dce_dccg {TYPE_1__ base; } ;
struct dccg {int dummy; } ;
struct dc_context {struct dc* dc; } ;
struct dc {TYPE_2__* res_pool; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* set_psr_wait_loop ) (struct dmcu*,int) ;} ;
struct TYPE_5__ {struct dmcu* dmcu; } ;

/* Variables and functions */
 struct dce_dccg* TO_DCE_CLOCKS (struct dccg*) ; 
 int dce_set_clock (struct dccg*,int) ; 
 int /*<<< orphan*/  stub1 (struct dmcu*,int) ; 

__attribute__((used)) static int dce_psr_set_clock(
	struct dccg *clk,
	int requested_clk_khz)
{
	struct dce_dccg *clk_dce = TO_DCE_CLOCKS(clk);
	struct dc_context *ctx = clk_dce->base.ctx;
	struct dc *core_dc = ctx->dc;
	struct dmcu *dmcu = core_dc->res_pool->dmcu;
	int actual_clk_khz = requested_clk_khz;

	actual_clk_khz = dce_set_clock(clk, requested_clk_khz);

	dmcu->funcs->set_psr_wait_loop(dmcu, actual_clk_khz / 1000 / 7);
	return actual_clk_khz;
}