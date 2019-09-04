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
typedef  size_t uint32_t ;
struct pll_settings {int dummy; } ;
struct pixel_clk_params {size_t controller_id; } ;
struct fixed31_32 {int dummy; } ;
struct dce110_clk_src {int /*<<< orphan*/  ref_freq_khz; } ;
struct clock_source {int dummy; } ;

/* Variables and functions */
 size_t CONTROLLER_ID_D0 ; 
 int /*<<< orphan*/  DP_DTO0_ENABLE ; 
 int /*<<< orphan*/  DP_DTO0_MODULO ; 
 int /*<<< orphan*/  DP_DTO0_PHASE ; 
 int /*<<< orphan*/ * MODULO ; 
 int /*<<< orphan*/ * PHASE ; 
 int /*<<< orphan*/ * PIXEL_RATE_CNTL ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct dce110_clk_src* TO_DCE110_CLK_SRC (struct clock_source*) ; 
 struct fixed31_32 dc_fixpt_div_int (struct fixed31_32,size_t) ; 
 struct fixed31_32 dc_fixpt_from_int (int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_mul_int (struct fixed31_32,size_t) ; 
 size_t dc_fixpt_round (struct fixed31_32) ; 
 size_t dce110_get_dp_pixel_rate_from_combo_phy_pll (struct clock_source*,struct pixel_clk_params*,struct pll_settings*) ; 

__attribute__((used)) static uint32_t dce110_get_d_to_pixel_rate_in_hz(
	struct clock_source *cs,
	struct pixel_clk_params *pix_clk_params,
	struct pll_settings *pll_settings)
{
	uint32_t inst = pix_clk_params->controller_id - CONTROLLER_ID_D0;
	struct dce110_clk_src *clk_src = TO_DCE110_CLK_SRC(cs);
	int dto_enabled = 0;
	struct fixed31_32 pix_rate;

	REG_GET(PIXEL_RATE_CNTL[inst], DP_DTO0_ENABLE, &dto_enabled);

	if (dto_enabled) {
		uint32_t phase = 0;
		uint32_t modulo = 0;
		REG_GET(PHASE[inst], DP_DTO0_PHASE, &phase);
		REG_GET(MODULO[inst], DP_DTO0_MODULO, &modulo);

		if (modulo == 0) {
			return 0;
		}

		pix_rate = dc_fixpt_from_int(clk_src->ref_freq_khz);
		pix_rate = dc_fixpt_mul_int(pix_rate, 1000);
		pix_rate = dc_fixpt_mul_int(pix_rate, phase);
		pix_rate = dc_fixpt_div_int(pix_rate, modulo);

		return dc_fixpt_round(pix_rate);
	} else {
		return dce110_get_dp_pixel_rate_from_combo_phy_pll(cs, pix_clk_params, pll_settings);
	}
}