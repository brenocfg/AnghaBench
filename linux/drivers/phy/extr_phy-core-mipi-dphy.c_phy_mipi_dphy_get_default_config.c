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
struct phy_configure_opts_mipi_dphy {int clk_post; int clk_pre; int clk_prepare; int clk_settle; int clk_trail; int clk_zero; int hs_exit; int hs_prepare; int hs_zero; int hs_settle; int hs_skip; int init; int lpx; int ta_get; int ta_go; int ta_sure; int wakeup; unsigned long long hs_clk_rate; unsigned int lanes; int /*<<< orphan*/  hs_trail; scalar_t__ eot; scalar_t__ d_term_en; scalar_t__ clk_term_en; scalar_t__ clk_miss; } ;

/* Variables and functions */
 unsigned long long ALIGN (int /*<<< orphan*/ ,unsigned long long) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PSEC_PER_SEC ; 
 int /*<<< orphan*/  do_div (unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  max (int,int) ; 

int phy_mipi_dphy_get_default_config(unsigned long pixel_clock,
				     unsigned int bpp,
				     unsigned int lanes,
				     struct phy_configure_opts_mipi_dphy *cfg)
{
	unsigned long long hs_clk_rate;
	unsigned long long ui;

	if (!cfg)
		return -EINVAL;

	hs_clk_rate = pixel_clock * bpp;
	do_div(hs_clk_rate, lanes);

	ui = ALIGN(PSEC_PER_SEC, hs_clk_rate);
	do_div(ui, hs_clk_rate);

	cfg->clk_miss = 0;
	cfg->clk_post = 60000 + 52 * ui;
	cfg->clk_pre = 8000;
	cfg->clk_prepare = 38000;
	cfg->clk_settle = 95000;
	cfg->clk_term_en = 0;
	cfg->clk_trail = 60000;
	cfg->clk_zero = 262000;
	cfg->d_term_en = 0;
	cfg->eot = 0;
	cfg->hs_exit = 100000;
	cfg->hs_prepare = 40000 + 4 * ui;
	cfg->hs_zero = 105000 + 6 * ui;
	cfg->hs_settle = 85000 + 6 * ui;
	cfg->hs_skip = 40000;

	/*
	 * The MIPI D-PHY specification (Section 6.9, v1.2, Table 14, Page 40)
	 * contains this formula as:
	 *
	 *     T_HS-TRAIL = max(n * 8 * ui, 60 + n * 4 * ui)
	 *
	 * where n = 1 for forward-direction HS mode and n = 4 for reverse-
	 * direction HS mode. There's only one setting and this function does
	 * not parameterize on anything other that ui, so this code will
	 * assumes that reverse-direction HS mode is supported and uses n = 4.
	 */
	cfg->hs_trail = max(4 * 8 * ui, 60000 + 4 * 4 * ui);

	cfg->init = 100;
	cfg->lpx = 60000;
	cfg->ta_get = 5 * cfg->lpx;
	cfg->ta_go = 4 * cfg->lpx;
	cfg->ta_sure = 2 * cfg->lpx;
	cfg->wakeup = 1000;

	cfg->hs_clk_rate = hs_clk_rate;
	cfg->lanes = lanes;

	return 0;
}