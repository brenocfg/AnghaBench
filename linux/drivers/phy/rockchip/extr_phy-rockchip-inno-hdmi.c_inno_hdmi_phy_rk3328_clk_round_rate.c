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
struct pre_pll_config {unsigned long pixclock; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 struct pre_pll_config* pre_pll_cfg_table ; 

__attribute__((used)) static long inno_hdmi_phy_rk3328_clk_round_rate(struct clk_hw *hw,
						unsigned long rate,
						unsigned long *parent_rate)
{
	const struct pre_pll_config *cfg = pre_pll_cfg_table;

	for (; cfg->pixclock != 0; cfg++)
		if (cfg->pixclock == rate)
			break;

	if (cfg->pixclock == 0)
		return -EINVAL;

	return cfg->pixclock;
}