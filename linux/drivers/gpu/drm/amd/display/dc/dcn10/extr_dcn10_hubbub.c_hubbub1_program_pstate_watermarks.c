#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_9__ ;
typedef  struct TYPE_33__   TYPE_8__ ;
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;
typedef  struct TYPE_25__   TYPE_17__ ;
typedef  struct TYPE_24__   TYPE_16__ ;
typedef  struct TYPE_23__   TYPE_15__ ;
typedef  struct TYPE_22__   TYPE_14__ ;
typedef  struct TYPE_21__   TYPE_13__ ;
typedef  struct TYPE_20__   TYPE_12__ ;
typedef  struct TYPE_19__   TYPE_11__ ;
typedef  struct TYPE_18__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct hubbub {int dummy; } ;
struct TYPE_24__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_25__ {TYPE_16__ cstate_pstate; } ;
struct TYPE_19__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_20__ {TYPE_11__ cstate_pstate; } ;
struct TYPE_32__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_33__ {TYPE_7__ cstate_pstate; } ;
struct TYPE_28__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_29__ {TYPE_3__ cstate_pstate; } ;
struct dcn_watermark_set {TYPE_17__ d; TYPE_12__ c; TYPE_8__ b; TYPE_4__ a; } ;
struct TYPE_21__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_22__ {TYPE_13__ cstate_pstate; } ;
struct TYPE_34__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_18__ {TYPE_9__ cstate_pstate; } ;
struct TYPE_30__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_31__ {TYPE_5__ cstate_pstate; } ;
struct TYPE_26__ {scalar_t__ pstate_change_ns; } ;
struct TYPE_27__ {TYPE_1__ cstate_pstate; } ;
struct TYPE_23__ {TYPE_14__ d; TYPE_10__ c; TYPE_6__ b; TYPE_2__ a; } ;
struct dcn10_hubbub {TYPE_15__ watermarks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D ; 
 int /*<<< orphan*/  DC_LOG_BANDWIDTH_CALCS (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  convert_and_clamp (scalar_t__,unsigned int,int) ; 

void hubbub1_program_pstate_watermarks(
		struct hubbub *hubbub,
		struct dcn_watermark_set *watermarks,
		unsigned int refclk_mhz,
		bool safe_to_lower)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uint32_t prog_wm_value;

	/* clock state A */
	if (safe_to_lower || watermarks->a.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.a.cstate_pstate.pstate_change_ns) {
		hubbub1->watermarks.a.cstate_pstate.pstate_change_ns =
				watermarks->a.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->a.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->a.cstate_pstate.pstate_change_ns, prog_wm_value);
	}

	/* clock state B */
	if (safe_to_lower || watermarks->b.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.b.cstate_pstate.pstate_change_ns) {
		hubbub1->watermarks.b.cstate_pstate.pstate_change_ns =
				watermarks->b.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->b.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->b.cstate_pstate.pstate_change_ns, prog_wm_value);
	}

	/* clock state C */
	if (safe_to_lower || watermarks->c.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.c.cstate_pstate.pstate_change_ns) {
		hubbub1->watermarks.c.cstate_pstate.pstate_change_ns =
				watermarks->c.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->c.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->c.cstate_pstate.pstate_change_ns, prog_wm_value);
	}

	/* clock state D */
	if (safe_to_lower || watermarks->d.cstate_pstate.pstate_change_ns
			> hubbub1->watermarks.d.cstate_pstate.pstate_change_ns) {
		hubbub1->watermarks.d.cstate_pstate.pstate_change_ns =
				watermarks->d.cstate_pstate.pstate_change_ns;
		prog_wm_value = convert_and_clamp(
				watermarks->d.cstate_pstate.pstate_change_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, 0,
				DCHUBBUB_ARB_ALLOW_DRAM_CLK_CHANGE_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("DRAM_CLK_CHANGE_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n\n",
			watermarks->d.cstate_pstate.pstate_change_ns, prog_wm_value);
	}
}