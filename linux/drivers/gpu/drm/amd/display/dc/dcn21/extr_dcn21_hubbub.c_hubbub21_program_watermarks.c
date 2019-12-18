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
struct hubbub {TYPE_3__* ctx; } ;
struct dcn_watermark_set {int dummy; } ;
struct dcn20_hubbub {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dc; } ;
struct TYPE_4__ {int /*<<< orphan*/  disable_stutter; } ;
struct TYPE_5__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_DF_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_HOSTVM_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_MAX_QOS_COMMIT_THRESHOLD ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_MIN_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_MIN_REQ_OUTSTAND_COMMIT_THRESHOLD ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_SAT_LEVEL ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 struct dcn20_hubbub* TO_DCN20_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  hubbub1_allow_self_refresh_control (struct hubbub*,int) ; 
 int /*<<< orphan*/  hubbub21_program_pstate_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 
 int /*<<< orphan*/  hubbub21_program_stutter_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 
 int /*<<< orphan*/  hubbub21_program_urgent_watermarks (struct hubbub*,struct dcn_watermark_set*,unsigned int,int) ; 

void hubbub21_program_watermarks(
		struct hubbub *hubbub,
		struct dcn_watermark_set *watermarks,
		unsigned int refclk_mhz,
		bool safe_to_lower)
{
	struct dcn20_hubbub *hubbub1 = TO_DCN20_HUBBUB(hubbub);

	hubbub21_program_urgent_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);
	hubbub21_program_stutter_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);
	hubbub21_program_pstate_watermarks(hubbub, watermarks, refclk_mhz, safe_to_lower);

	/*
	 * The DCHub arbiter has a mechanism to dynamically rate limit the DCHub request stream to the fabric.
	 * If the memory controller is fully utilized and the DCHub requestors are
	 * well ahead of their amortized schedule, then it is safe to prevent the next winner
	 * from being committed and sent to the fabric.
	 * The utilization of the memory controller is approximated by ensuring that
	 * the number of outstanding requests is greater than a threshold specified
	 * by the ARB_MIN_REQ_OUTSTANDING. To determine that the DCHub requestors are well ahead of the amortized schedule,
	 * the slack of the next winner is compared with the ARB_SAT_LEVEL in DLG RefClk cycles.
	 *
	 * TODO: Revisit request limit after figure out right number. request limit for Renoir isn't decided yet, set maximum value (0x1FF)
	 * to turn off it for now.
	 */
	REG_SET(DCHUBBUB_ARB_SAT_LEVEL, 0,
			DCHUBBUB_ARB_SAT_LEVEL, 60 * refclk_mhz);
	REG_UPDATE_2(DCHUBBUB_ARB_DF_REQ_OUTSTAND,
			DCHUBBUB_ARB_MIN_REQ_OUTSTAND, 0x1FF,
			DCHUBBUB_ARB_MIN_REQ_OUTSTAND_COMMIT_THRESHOLD, 0xA);
	REG_UPDATE(DCHUBBUB_ARB_HOSTVM_CNTL,
			DCHUBBUB_ARB_MAX_QOS_COMMIT_THRESHOLD, 0xF);

	hubbub1_allow_self_refresh_control(hubbub, !hubbub->ctx->dc->debug.disable_stutter);
}