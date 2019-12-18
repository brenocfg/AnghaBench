#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct hubbub {int dummy; } ;
struct TYPE_18__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct TYPE_15__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct TYPE_13__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct TYPE_11__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct dcn_watermark_set {TYPE_9__ d; TYPE_6__ c; TYPE_4__ b; TYPE_2__ a; } ;
struct TYPE_16__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct TYPE_14__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct TYPE_12__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct TYPE_10__ {scalar_t__ urgent_ns; scalar_t__ pte_meta_urgent_ns; } ;
struct TYPE_17__ {TYPE_7__ d; TYPE_5__ c; TYPE_3__ b; TYPE_1__ a; } ;
struct dcn10_hubbub {TYPE_8__ watermarks; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D ; 
 int /*<<< orphan*/  DC_LOG_BANDWIDTH_CALCS (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dcn10_hubbub* TO_DCN10_HUBBUB (struct hubbub*) ; 
 int /*<<< orphan*/  convert_and_clamp (scalar_t__,unsigned int,int) ; 

void hubbub1_program_urgent_watermarks(
		struct hubbub *hubbub,
		struct dcn_watermark_set *watermarks,
		unsigned int refclk_mhz,
		bool safe_to_lower)
{
	struct dcn10_hubbub *hubbub1 = TO_DCN10_HUBBUB(hubbub);
	uint32_t prog_wm_value;

	/* Repeat for water mark set A, B, C and D. */
	/* clock state A */
	if (safe_to_lower || watermarks->a.urgent_ns > hubbub1->watermarks.a.urgent_ns) {
		hubbub1->watermarks.a.urgent_ns = watermarks->a.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->a.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_A, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->a.pte_meta_urgent_ns > hubbub1->watermarks.a.pte_meta_urgent_ns) {
		hubbub1->watermarks.a.pte_meta_urgent_ns = watermarks->a.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->a.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_A, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_A calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->a.pte_meta_urgent_ns, prog_wm_value);
	}

	/* clock state B */
	if (safe_to_lower || watermarks->b.urgent_ns > hubbub1->watermarks.b.urgent_ns) {
		hubbub1->watermarks.b.urgent_ns = watermarks->b.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->b.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_B, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->b.pte_meta_urgent_ns > hubbub1->watermarks.b.pte_meta_urgent_ns) {
		hubbub1->watermarks.b.pte_meta_urgent_ns = watermarks->b.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->b.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_B, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_B calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->b.pte_meta_urgent_ns, prog_wm_value);
	}

	/* clock state C */
	if (safe_to_lower || watermarks->c.urgent_ns > hubbub1->watermarks.c.urgent_ns) {
		hubbub1->watermarks.c.urgent_ns = watermarks->c.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->c.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_C, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->c.pte_meta_urgent_ns > hubbub1->watermarks.c.pte_meta_urgent_ns) {
		hubbub1->watermarks.c.pte_meta_urgent_ns = watermarks->c.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->c.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_C, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_C calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->c.pte_meta_urgent_ns, prog_wm_value);
	}

	/* clock state D */
	if (safe_to_lower || watermarks->d.urgent_ns > hubbub1->watermarks.d.urgent_ns) {
		hubbub1->watermarks.d.urgent_ns = watermarks->d.urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->d.urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_SET(DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, 0,
				DCHUBBUB_ARB_DATA_URGENCY_WATERMARK_D, prog_wm_value);

		DC_LOG_BANDWIDTH_CALCS("URGENCY_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.urgent_ns, prog_wm_value);
	}

	if (safe_to_lower || watermarks->d.pte_meta_urgent_ns > hubbub1->watermarks.d.pte_meta_urgent_ns) {
		hubbub1->watermarks.d.pte_meta_urgent_ns = watermarks->d.pte_meta_urgent_ns;
		prog_wm_value = convert_and_clamp(watermarks->d.pte_meta_urgent_ns,
				refclk_mhz, 0x1fffff);
		REG_WRITE(DCHUBBUB_ARB_PTE_META_URGENCY_WATERMARK_D, prog_wm_value);
		DC_LOG_BANDWIDTH_CALCS("PTE_META_URGENCY_WATERMARK_D calculated =%d\n"
			"HW register value = 0x%x\n",
			watermarks->d.pte_meta_urgent_ns, prog_wm_value);
	}
}