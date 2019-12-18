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
typedef  scalar_t__ uint32_t ;
struct dcn_dccg {int dummy; } ;
struct dccg {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_CRITICAL (int) ; 
 int /*<<< orphan*/  REFCLK_CLOCK_EN ; 
 int /*<<< orphan*/  REFCLK_CNTL ; 
 int /*<<< orphan*/  REFCLK_SRC_SEL ; 
 int /*<<< orphan*/  REG_GET_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct dcn_dccg* TO_DCN_DCCG (struct dccg*) ; 

void dccg2_get_dccg_ref_freq(struct dccg *dccg,
		unsigned int xtalin_freq_inKhz,
		unsigned int *dccg_ref_freq_inKhz)
{
	struct dcn_dccg *dccg_dcn = TO_DCN_DCCG(dccg);
	uint32_t clk_en = 0;
	uint32_t clk_sel = 0;

	REG_GET_2(REFCLK_CNTL, REFCLK_CLOCK_EN, &clk_en, REFCLK_SRC_SEL, &clk_sel);

	if (clk_en != 0) {
		// DCN20 has never been validated for non-xtalin as reference
		// frequency.  There's actually no way for DC to determine what
		// frequency a non-xtalin source is.
		ASSERT_CRITICAL(false);
	}

	*dccg_ref_freq_inKhz = xtalin_freq_inKhz;

	return;
}