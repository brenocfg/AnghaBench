#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct hubbub {TYPE_8__* ctx; } ;
struct dcn_watermark_set {int dummy; } ;
struct TYPE_13__ {TYPE_4__* ctx; } ;
struct dcn20_hubbub {TYPE_5__ base; } ;
struct TYPE_16__ {TYPE_7__* dc; } ;
struct TYPE_14__ {int /*<<< orphan*/  disable_stutter; } ;
struct TYPE_15__ {TYPE_6__ debug; } ;
struct TYPE_12__ {TYPE_3__* dc; } ;
struct TYPE_11__ {TYPE_2__* clk_mgr; } ;
struct TYPE_9__ {int prev_p_state_change_support; int p_state_change_support; } ;
struct TYPE_10__ {TYPE_1__ clks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_DF_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_MIN_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_SAT_LEVEL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dcn20_hubbub* TO_DCN20_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  hubbub1_allow_self_refresh_control (struct hubbub*,int) ; 
 int /*<<< orphan*/  hubbub1_program_pstate_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 
 int /*<<< orphan*/  hubbub1_program_stutter_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 
 int /*<<< orphan*/  hubbub1_program_urgent_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 

__attribute__((used)) static void hubbub2_program_watermarks(
		struct hubbub *hubbub,
		struct dcn_watermark_set *watermarks,
		unsigned int refclk_mhz,
		bool safe_to_lower)
{
	struct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);
	/*
	 * Need to clamp to max of the register values (i.e. no wrap)
	 * for dcn1, all wm registers are 21-bit wide
	 */
	hubbub1_program_urgent_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);
	hubbub1_program_stutter_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);

	/*
	 * There's a special case when going from p-state support to p-state unsupported
	 * here we are going to LOWER watermarks to go to dummy p-state only, but this has
	 * to be done prepare_bandwidth, not optimize
	 */
	if (hubbub1->base.ctx->dc->clk_mgr->clks.prev_p_state_change_support == true &&
		hubbub1->base.ctx->dc->clk_mgr->clks.p_state_change_support == false)
		safe_to_lower = true;

	hubbub1_program_pstate_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);

	REG_SET(DCHUBBUB_ARB_SAT_LEVEL, 0,
			DCHUBBUB_ARB_SAT_LEVEL, 60 * refclk_mhz);
	REG_UPDATE(DCHUBBUB_ARB_DF_REQ_OUTSTAND, DCHUBBUB_ARB_MIN_REQ_OUTSTAND, 180);

	hubbub1_allow_self_refresh_control(hubbub, !hubbub->ctx->dc->debug.disable_stutter);
}