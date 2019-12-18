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
struct hubbub {TYPE_1__* ctx; } ;
struct dcn_watermark_set {int dummy; } ;
struct dcn10_hubbub {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  disable_stutter; } ;
struct TYPE_6__ {TYPE_2__ debug; } ;
struct TYPE_4__ {TYPE_3__* dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_DF_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_MIN_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_SAT_LEVEL ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_WATERMARK_CHANGE_DONE_INTERRUPT_DISABLE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  hubbub1_allow_self_refresh_control (struct hubbub*,int) ; 
 int /*<<< orphan*/  hubbub1_program_pstate_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 
 int /*<<< orphan*/  hubbub1_program_stutter_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 
 int /*<<< orphan*/  hubbub1_program_urgent_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 

void hubbub1_program_watermarks(
		struct hubbub *hubbub,
		struct dcn_watermark_set *watermarks,
		unsigned int refclk_mhz,
		bool safe_to_lower)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	/*
	 * Need to clamp to max of the register values (i.e. no wrap)
	 * for dcn1, all wm registers are 21-bit wide
	 */
	hubbub1_program_urgent_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);
	hubbub1_program_stutter_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);
	hubbub1_program_pstate_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);

	REG_UPDATE(DCHUBBUB_ARB_SAT_LEVEL,
			DCHUBBUB_ARB_SAT_LEVEL, 60 * refclk_mhz);
	REG_UPDATE(DCHUBBUB_ARB_DF_REQ_OUTSTAND,
			DCHUBBUB_ARB_MIN_REQ_OUTSTAND, 68);

	hubbub1_allow_self_refresh_control(hubbub, !hubbub->ctx->dc->debug.disable_stutter);

#if 0
	REG_UPDATE_2(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_DONE_INTERRUPT_DISABLE, 1,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, 1);
#endif
}