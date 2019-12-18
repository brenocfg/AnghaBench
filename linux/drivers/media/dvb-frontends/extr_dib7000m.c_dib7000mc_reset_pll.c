#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct dibx000_bandwidth_config {int pll_prediv; int pll_ratio; int IO_CLK_en_core; int bypclk_div; int enable_refdiv; int pll_range; int pll_reset; int pll_bypass; int modulo; int ADClkSrc; } ;
struct TYPE_2__ {struct dibx000_bandwidth_config* bw; } ;
struct dib7000m_state {TYPE_1__ cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib7000m_reset_pll_common (struct dib7000m_state*,struct dibx000_bandwidth_config const*) ; 
 int /*<<< orphan*/  dib7000m_write_word (struct dib7000m_state*,int,int) ; 

__attribute__((used)) static void dib7000mc_reset_pll(struct dib7000m_state *state)
{
	const struct dibx000_bandwidth_config *bw = state->cfg.bw;
	u16 clk_cfg1;

	// clk_cfg0
	dib7000m_write_word(state, 907, (bw->pll_prediv << 8) | (bw->pll_ratio << 0));

	// clk_cfg1
	//dib7000m_write_word(state, 908, (1 << 14) | (3 << 12) |(0 << 11) |
	clk_cfg1 = (0 << 14) | (3 << 12) |(0 << 11) |
			(bw->IO_CLK_en_core << 10) | (bw->bypclk_div << 5) | (bw->enable_refdiv << 4) |
			(1 << 3) | (bw->pll_range << 1) | (bw->pll_reset << 0);
	dib7000m_write_word(state, 908, clk_cfg1);
	clk_cfg1 = (clk_cfg1 & 0xfff7) | (bw->pll_bypass << 3);
	dib7000m_write_word(state, 908, clk_cfg1);

	// smpl_cfg
	dib7000m_write_word(state, 910, (1 << 12) | (2 << 10) | (bw->modulo << 8) | (bw->ADClkSrc << 7));

	dib7000m_reset_pll_common(state, bw);
}