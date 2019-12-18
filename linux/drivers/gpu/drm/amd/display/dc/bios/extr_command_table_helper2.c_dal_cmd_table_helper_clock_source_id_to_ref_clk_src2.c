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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum clock_source_id { ____Placeholder_clock_source_id } clock_source_id ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_TO_DEBUGGER () ; 
#define  CLOCK_SOURCE_ID_EXTERNAL 131 
#define  CLOCK_SOURCE_ID_PLL1 130 
#define  CLOCK_SOURCE_ID_PLL2 129 
#define  CLOCK_SOURCE_ID_UNDEFINED 128 
 int /*<<< orphan*/  ENCODER_REFCLK_SRC_EXTCLK ; 
 int /*<<< orphan*/  ENCODER_REFCLK_SRC_INVALID ; 
 int /*<<< orphan*/  ENCODER_REFCLK_SRC_P1PLL ; 
 int /*<<< orphan*/  ENCODER_REFCLK_SRC_P2PLL ; 

bool dal_cmd_table_helper_clock_source_id_to_ref_clk_src2(
	enum clock_source_id id,
	uint32_t *ref_clk_src_id)
{
	if (ref_clk_src_id == NULL) {
		BREAK_TO_DEBUGGER();
		return false;
	}

	switch (id) {
	case CLOCK_SOURCE_ID_PLL1:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_P1PLL;
		return true;
	case CLOCK_SOURCE_ID_PLL2:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_P2PLL;
		return true;
	/*TODO:case CLOCK_SOURCE_ID_DCPLL:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_DCPLL;
		return true;
	*/
	case CLOCK_SOURCE_ID_EXTERNAL:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_EXTCLK;
		return true;
	case CLOCK_SOURCE_ID_UNDEFINED:
		*ref_clk_src_id = ENCODER_REFCLK_SRC_INVALID;
		return true;
	default:
		/* Unsupported clock source id */
		BREAK_TO_DEBUGGER();
		return false;
	}
}