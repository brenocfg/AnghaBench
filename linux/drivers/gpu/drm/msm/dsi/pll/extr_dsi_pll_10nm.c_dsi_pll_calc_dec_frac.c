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
typedef  int u64 ;
typedef  int u32 ;
struct dsi_pll_regs {int pll_prop_gain_rate; int pll_clock_inverters; int decimal_div_start; int frac_div_start_low; int frac_div_start_mid; int frac_div_start_high; int /*<<< orphan*/  pll_lockdet_rate; } ;
struct dsi_pll_config {int frac_bits; int /*<<< orphan*/  lock_timer; scalar_t__ disable_prescaler; } ;
struct dsi_pll_10nm {int vco_ref_clk_rate; int vco_current_rate; struct dsi_pll_regs reg_setup; struct dsi_pll_config pll_configuration; } ;

/* Variables and functions */
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  div_u64_rem (int,int,int*) ; 

__attribute__((used)) static void dsi_pll_calc_dec_frac(struct dsi_pll_10nm *pll)
{
	struct dsi_pll_config *config = &pll->pll_configuration;
	struct dsi_pll_regs *regs = &pll->reg_setup;
	u64 fref = pll->vco_ref_clk_rate;
	u64 pll_freq;
	u64 divider;
	u64 dec, dec_multiple;
	u32 frac;
	u64 multiplier;

	pll_freq = pll->vco_current_rate;

	if (config->disable_prescaler)
		divider = fref;
	else
		divider = fref * 2;

	multiplier = 1 << config->frac_bits;
	dec_multiple = div_u64(pll_freq * multiplier, divider);
	div_u64_rem(dec_multiple, multiplier, &frac);

	dec = div_u64(dec_multiple, multiplier);

	if (pll_freq <= 1900000000UL)
		regs->pll_prop_gain_rate = 8;
	else if (pll_freq <= 3000000000UL)
		regs->pll_prop_gain_rate = 10;
	else
		regs->pll_prop_gain_rate = 12;
	if (pll_freq < 1100000000UL)
		regs->pll_clock_inverters = 8;
	else
		regs->pll_clock_inverters = 0;

	regs->pll_lockdet_rate = config->lock_timer;
	regs->decimal_div_start = dec;
	regs->frac_div_start_low = (frac & 0xff);
	regs->frac_div_start_mid = (frac & 0xff00) >> 8;
	regs->frac_div_start_high = (frac & 0x30000) >> 16;
}