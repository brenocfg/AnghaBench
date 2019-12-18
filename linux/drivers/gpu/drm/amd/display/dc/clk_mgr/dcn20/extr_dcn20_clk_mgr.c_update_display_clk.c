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
struct clk_mgr_internal {unsigned int dentist_vco_freq_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  DENTIST_DISPCLK_CNTL ; 
 int /*<<< orphan*/  DENTIST_DISPCLK_WDIVIDER ; 
 unsigned int DENTIST_DIVIDER_RANGE_SCALE_FACTOR ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dentist_get_did_from_divider (int) ; 

__attribute__((used)) static void update_display_clk(struct clk_mgr_internal *clk_mgr, unsigned int khz)
{
	int disp_divider = DENTIST_DIVIDER_RANGE_SCALE_FACTOR
			* clk_mgr->dentist_vco_freq_khz / khz;

	uint32_t dispclk_wdivider = dentist_get_did_from_divider(disp_divider);

	REG_UPDATE(DENTIST_DISPCLK_CNTL,
			DENTIST_DISPCLK_WDIVIDER, dispclk_wdivider);
}