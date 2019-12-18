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
struct fixed31_32 {unsigned int value; } ;
struct clk_mgr_internal {int /*<<< orphan*/  dfs_ref_freq_khz; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK1_CLK_PLL_REQ ; 
 int /*<<< orphan*/  FbMult_frac ; 
 int /*<<< orphan*/  FbMult_int ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int dc_fixpt_floor (struct fixed31_32) ; 
 struct fixed31_32 dc_fixpt_from_int (unsigned int) ; 
 struct fixed31_32 dc_fixpt_mul_int (struct fixed31_32,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_vco_frequency_from_reg(struct clk_mgr_internal *clk_mgr)
{
	/* get FbMult value */
	struct fixed31_32 pll_req;
	unsigned int fbmult_frac_val = 0;
	unsigned int fbmult_int_val = 0;


	/*
	 * Register value of fbmult is in 8.16 format, we are converting to 31.32
	 * to leverage the fix point operations available in driver
	 */

	REG_GET(CLK1_CLK_PLL_REQ, FbMult_frac, &fbmult_frac_val); /* 16 bit fractional part*/
	REG_GET(CLK1_CLK_PLL_REQ, FbMult_int, &fbmult_int_val); /* 8 bit integer part */

	pll_req = dc_fixpt_from_int(fbmult_int_val);

	/*
	 * since fractional part is only 16 bit in register definition but is 32 bit
	 * in our fix point definiton, need to shift left by 16 to obtain correct value
	 */
	pll_req.value |= fbmult_frac_val << 16;

	/* multiply by REFCLK period */
	pll_req = dc_fixpt_mul_int(pll_req, clk_mgr->dfs_ref_freq_khz);

	/* integer part is now VCO frequency in kHz */
	return dc_fixpt_floor(pll_req);
}