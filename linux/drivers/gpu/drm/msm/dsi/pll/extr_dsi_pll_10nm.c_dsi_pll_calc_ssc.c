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
struct dsi_pll_regs {int frac_div_start_low; int frac_div_start_mid; int frac_div_start_high; int decimal_div_start; int ssc_div_per_low; int ssc_div_per_high; int ssc_stepsize_low; int ssc_stepsize_high; int ssc_adjper_low; int ssc_adjper_high; int /*<<< orphan*/  ssc_control; } ;
struct dsi_pll_config {int ssc_adj_per; int frac_bits; int ssc_offset; scalar_t__ ssc_center; int /*<<< orphan*/  ssc_freq; int /*<<< orphan*/  ref_freq; int /*<<< orphan*/  enable_ssc; } ;
struct dsi_pll_10nm {struct dsi_pll_regs reg_setup; struct dsi_pll_config pll_configuration; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int DIV_ROUND_CLOSEST (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int /*<<< orphan*/  SSC_CENTER ; 
 int div_u64 (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 

__attribute__((used)) static void dsi_pll_calc_ssc(struct dsi_pll_10nm *pll)
{
	struct dsi_pll_config *config = &pll->pll_configuration;
	struct dsi_pll_regs *regs = &pll->reg_setup;
	u32 ssc_per;
	u32 ssc_mod;
	u64 ssc_step_size;
	u64 frac;

	if (!config->enable_ssc) {
		DBG("SSC not enabled\n");
		return;
	}

	ssc_per = DIV_ROUND_CLOSEST(config->ref_freq, config->ssc_freq) / 2 - 1;
	ssc_mod = (ssc_per + 1) % (config->ssc_adj_per + 1);
	ssc_per -= ssc_mod;

	frac = regs->frac_div_start_low |
			(regs->frac_div_start_mid << 8) |
			(regs->frac_div_start_high << 16);
	ssc_step_size = regs->decimal_div_start;
	ssc_step_size *= (1 << config->frac_bits);
	ssc_step_size += frac;
	ssc_step_size *= config->ssc_offset;
	ssc_step_size *= (config->ssc_adj_per + 1);
	ssc_step_size = div_u64(ssc_step_size, (ssc_per + 1));
	ssc_step_size = DIV_ROUND_CLOSEST_ULL(ssc_step_size, 1000000);

	regs->ssc_div_per_low = ssc_per & 0xFF;
	regs->ssc_div_per_high = (ssc_per & 0xFF00) >> 8;
	regs->ssc_stepsize_low = (u32)(ssc_step_size & 0xFF);
	regs->ssc_stepsize_high = (u32)((ssc_step_size & 0xFF00) >> 8);
	regs->ssc_adjper_low = config->ssc_adj_per & 0xFF;
	regs->ssc_adjper_high = (config->ssc_adj_per & 0xFF00) >> 8;

	regs->ssc_control = config->ssc_center ? SSC_CENTER : 0;

	pr_debug("SCC: Dec:%d, frac:%llu, frac_bits:%d\n",
		 regs->decimal_div_start, frac, config->frac_bits);
	pr_debug("SSC: div_per:0x%X, stepsize:0x%X, adjper:0x%X\n",
		 ssc_per, (u32)ssc_step_size, config->ssc_adj_per);
}