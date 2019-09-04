#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_20__ ;
typedef  struct TYPE_31__   TYPE_1__ ;
typedef  struct TYPE_30__   TYPE_19__ ;
typedef  struct TYPE_29__   TYPE_18__ ;
typedef  struct TYPE_28__   TYPE_17__ ;
typedef  struct TYPE_27__   TYPE_16__ ;
typedef  struct TYPE_26__   TYPE_15__ ;
typedef  struct TYPE_25__   TYPE_14__ ;
typedef  struct TYPE_24__   TYPE_13__ ;
typedef  struct TYPE_23__   TYPE_12__ ;
typedef  struct TYPE_22__   TYPE_11__ ;
typedef  struct TYPE_21__   TYPE_10__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_27__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_28__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_16__ cstate_pstate; } ;
struct TYPE_23__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_24__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_12__ cstate_pstate; } ;
struct TYPE_39__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_40__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_8__ cstate_pstate; } ;
struct TYPE_35__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_36__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_4__ cstate_pstate; } ;
struct TYPE_29__ {TYPE_17__ d; TYPE_13__ c; TYPE_9__ b; TYPE_5__ a; } ;
struct hubbub {TYPE_18__ watermarks; TYPE_3__* ctx; } ;
struct TYPE_30__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_32__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_19__ cstate_pstate; } ;
struct TYPE_25__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_26__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_14__ cstate_pstate; } ;
struct TYPE_21__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_22__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_10__ cstate_pstate; } ;
struct TYPE_37__ {scalar_t__ cstate_enter_plus_exit_ns; scalar_t__ cstate_exit_ns; scalar_t__ pstate_change_ns; } ;
struct TYPE_38__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; TYPE_6__ cstate_pstate; } ;
struct dcn_watermark_set {TYPE_20__ d; TYPE_15__ c; TYPE_11__ b; TYPE_7__ a; } ;
struct TYPE_34__ {TYPE_2__* dc; } ;
struct TYPE_31__ {scalar_t__ disable_stutter; } ;
struct TYPE_33__ {TYPE_1__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_VALUE ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DF_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DRAM_STATE_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_MIN_REQ_OUTSTAND ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_SAT_LEVEL ; 
 int /*<<< orphan*/  DC_LOG_BANDWIDTH_CALCS (char*,scalar_t__,int) ; 
 scalar_t__ REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_UPDATE_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int convert_and_clamp (scalar_t__,unsigned int,int) ; 

void hubbub1_program_watermarks(
		struct hubbub *hubbub,
		struct dcn_watermark_set *watermarks,
		unsigned int refclk_mhz,
		bool safe_to_lower)
{
	uint32_t force_en = hubbub->ctx->dc->debug.disable_stutter ? 1 : 0;
	/*
	 * Need to clamp to max of the register values (i.e. no wrap)
	 * for dcn1, all wm registers are 21-bit wide
	 */
	uint32_t prog_wm_value;


	/* Repeat for water mark set A, B, C and D. */
	/* clock state A */
	if (safe_to_lower || watermarks->a.urgent_ns > hubbub->watermarks.a.urgent_ns) {
		hubbub->watermarks.a.urgent_ns = watermarks->a.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->a.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->a.pte_meta_urgent_ns > hubbub->watermarks.a.pte_meta_urgent_ns) {
		hubbub->watermarks.a.pte_meta_urgent_ns = watermarks->a.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->a.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.pte_meta_urgent_ns, prog_wm_value);
	}

	if (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A)) {
		if (safe_to_lower || watermarks->a.cstate_pstate.cstate_enter_plus_exit_ns
				> hubbub->watermarks.a.cstate_pstate.cstate_enter_plus_exit_ns) {
			hubbub->watermarks.a.cstate_pstate.cstate_enter_plus_exit_ns =
					watermarks->a.cstate_pstate.cstate_enter_plus_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->a.cstate_pstate.cstate_enter_plus_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_A, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_A calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->a.cstate_pstate.cstate_enter_plus_exit_ns, prog_wm_value);
		}

		if (safe_to_lower || watermarks->a.cstate_pstate.cstate_exit_ns
				> hubbub->watermarks.a.cstate_pstate.cstate_exit_ns) {
			hubbub->watermarks.a.cstate_pstate.cstate_exit_ns =
					watermarks->a.cstate_pstate.cstate_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->a.cstate_pstate.cstate_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_A, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_A calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->a.cstate_pstate.cstate_exit_ns, prog_wm_value);
		}
	}

	if (safe_to_lower || watermarks->a.cstate_pstate.pstate_change_ns
			> hubbub->watermarks.a.cstate_pstate.pstate_change_ns) {
		hubbub->watermarks.a.cstate_pstate.pstate_change_ns =
				watermarks->a.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->a.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->a.cstate_pstate.pstate_change_ns, prog_wm_value);
	}

	/* clock state B */
	if (safe_to_lower || watermarks->b.urgent_ns > hubbub->watermarks.b.urgent_ns) {
		hubbub->watermarks.b.urgent_ns = watermarks->b.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->b.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->b.pte_meta_urgent_ns > hubbub->watermarks.b.pte_meta_urgent_ns) {
		hubbub->watermarks.b.pte_meta_urgent_ns = watermarks->b.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->b.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.pte_meta_urgent_ns, prog_wm_value);
	}

	if (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B)) {
		if (safe_to_lower || watermarks->b.cstate_pstate.cstate_enter_plus_exit_ns
				> hubbub->watermarks.b.cstate_pstate.cstate_enter_plus_exit_ns) {
			hubbub->watermarks.b.cstate_pstate.cstate_enter_plus_exit_ns =
					watermarks->b.cstate_pstate.cstate_enter_plus_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->b.cstate_pstate.cstate_enter_plus_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_B, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_B calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->b.cstate_pstate.cstate_enter_plus_exit_ns, prog_wm_value);
		}

		if (safe_to_lower || watermarks->b.cstate_pstate.cstate_exit_ns
				> hubbub->watermarks.b.cstate_pstate.cstate_exit_ns) {
			hubbub->watermarks.b.cstate_pstate.cstate_exit_ns =
					watermarks->b.cstate_pstate.cstate_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->b.cstate_pstate.cstate_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_B, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_B calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->b.cstate_pstate.cstate_exit_ns, prog_wm_value);
		}
	}

	if (safe_to_lower || watermarks->b.cstate_pstate.pstate_change_ns
			> hubbub->watermarks.b.cstate_pstate.pstate_change_ns) {
		hubbub->watermarks.b.cstate_pstate.pstate_change_ns =
				watermarks->b.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->b.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->b.cstate_pstate.pstate_change_ns, prog_wm_value);
	}

	/* clock state C */
	if (safe_to_lower || watermarks->c.urgent_ns > hubbub->watermarks.c.urgent_ns) {
		hubbub->watermarks.c.urgent_ns = watermarks->c.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->c.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->c.pte_meta_urgent_ns > hubbub->watermarks.c.pte_meta_urgent_ns) {
		hubbub->watermarks.c.pte_meta_urgent_ns = watermarks->c.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->c.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.pte_meta_urgent_ns, prog_wm_value);
	}

	if (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C)) {
		if (safe_to_lower || watermarks->c.cstate_pstate.cstate_enter_plus_exit_ns
				> hubbub->watermarks.c.cstate_pstate.cstate_enter_plus_exit_ns) {
			hubbub->watermarks.c.cstate_pstate.cstate_enter_plus_exit_ns =
					watermarks->c.cstate_pstate.cstate_enter_plus_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->c.cstate_pstate.cstate_enter_plus_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_C, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_C calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->c.cstate_pstate.cstate_enter_plus_exit_ns, prog_wm_value);
		}

		if (safe_to_lower || watermarks->c.cstate_pstate.cstate_exit_ns
				> hubbub->watermarks.c.cstate_pstate.cstate_exit_ns) {
			hubbub->watermarks.c.cstate_pstate.cstate_exit_ns =
					watermarks->c.cstate_pstate.cstate_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->c.cstate_pstate.cstate_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_C, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_C calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->c.cstate_pstate.cstate_exit_ns, prog_wm_value);
		}
	}

	if (safe_to_lower || watermarks->c.cstate_pstate.pstate_change_ns
			> hubbub->watermarks.c.cstate_pstate.pstate_change_ns) {
		hubbub->watermarks.c.cstate_pstate.pstate_change_ns =
				watermarks->c.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->c.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->c.cstate_pstate.pstate_change_ns, prog_wm_value);
	}

	/* clock state D */
	if (safe_to_lower || watermarks->d.urgent_ns > hubbub->watermarks.d.urgent_ns) {
		hubbub->watermarks.d.urgent_ns = watermarks->d.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->d.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->d.pte_meta_urgent_ns > hubbub->watermarks.d.pte_meta_urgent_ns) {
		hubbub->watermarks.d.pte_meta_urgent_ns = watermarks->d.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->d.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.pte_meta_urgent_ns, prog_wm_value);
	}

	if (REG(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D)) {
		if (safe_to_lower || watermarks->d.cstate_pstate.cstate_enter_plus_exit_ns
				> hubbub->watermarks.d.cstate_pstate.cstate_enter_plus_exit_ns) {
			hubbub->watermarks.d.cstate_pstate.cstate_enter_plus_exit_ns =
					watermarks->d.cstate_pstate.cstate_enter_plus_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->d.cstate_pstate.cstate_enter_plus_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_ENTER_WATERMARK_D, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_ENTER_EXIT_WATERMARK_D calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->d.cstate_pstate.cstate_enter_plus_exit_ns, prog_wm_value);
		}

		if (safe_to_lower || watermarks->d.cstate_pstate.cstate_exit_ns
				> hubbub->watermarks.d.cstate_pstate.cstate_exit_ns) {
			hubbub->watermarks.d.cstate_pstate.cstate_exit_ns =
					watermarks->d.cstate_pstate.cstate_exit_ns;
			prog_wm_value = convert_and_clamp(
					watermarks->d.cstate_pstate.cstate_exit_ns,
					refclk_mhz, 0x1fffff);
			REG_WRITE(DCHUBBUB_ARB_ALLOW_SR_EXIT_WATERMARK_D, prog_wm_value);
			DC_LOG_BANDWIDTH_CALCS("SR_EXIT_WATERMARK_D calculated =%d\n"
				"HW register value = 0x%x\n",
				watermarks->d.cstate_pstate.cstate_exit_ns, prog_wm_value);
		}
	}

	if (safe_to_lower || watermarks->d.cstate_pstate.pstate_change_ns
			> hubbub->watermarks.d.cstate_pstate.pstate_change_ns) {
		hubbub->watermarks.d.cstate_pstate.pstate_change_ns =
				watermarks->d.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->d.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->d.cstate_pstate.pstate_change_ns, prog_wm_value);
	}

	REG_UPDATE(DCHUBBUB_ARB_SAT_LEVEL,
			DCHUBBUB_ARB_SAT_LEVEL, 60 * refclk_mhz);
	REG_UPDATE(DCHUBBUB_ARB_DF_REQ_OUTSTAND,
			DCHUBBUB_ARB_MIN_REQ_OUTSTAND, 68);

	REG_UPDATE_2(DCHUBBUB_ARB_DRAM_STATE_CNTL,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_VALUE, 0,
			DCHUBBUB_ARB_ALLOW_SELF_REFRESH_FORCE_ENABLE, force_en);

#if 0
	REG_UPDATE_2(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_DONE_INTERRUPT_DISABLE, 1,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, 1);
#endif
}