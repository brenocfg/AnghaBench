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
struct dsi_pll_config {int output_div; int dec_bits; int frac_bits; int lock_timer; int ssc_freq; int ssc_offset; int ssc_adj_per; int thresh_cycles; int refclk_cycles; int div_override; int ignore_frac; int disable_prescaler; int enable_ssc; scalar_t__ ssc_center; int /*<<< orphan*/  ref_freq; } ;
struct dsi_pll_10nm {int /*<<< orphan*/  vco_ref_clk_rate; struct dsi_pll_config pll_configuration; } ;

/* Variables and functions */

__attribute__((used)) static void dsi_pll_setup_config(struct dsi_pll_10nm *pll)
{
	struct dsi_pll_config *config = &pll->pll_configuration;

	config->ref_freq = pll->vco_ref_clk_rate;
	config->output_div = 1;
	config->dec_bits = 8;
	config->frac_bits = 18;
	config->lock_timer = 64;
	config->ssc_freq = 31500;
	config->ssc_offset = 5000;
	config->ssc_adj_per = 2;
	config->thresh_cycles = 32;
	config->refclk_cycles = 256;

	config->div_override = false;
	config->ignore_frac = false;
	config->disable_prescaler = false;

	config->enable_ssc = false;
	config->ssc_center = 0;
}