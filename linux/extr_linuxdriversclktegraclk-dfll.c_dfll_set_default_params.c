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
typedef  int u32 ;
struct tegra_dfll {int sample_rate; int force_mode; int cf; int ci; int cg; int droop_ctrl; scalar_t__ cg_scale; int /*<<< orphan*/  ref_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DFLL_CONFIG ; 
 int DFLL_CONFIG_DIV_MASK ; 
 int /*<<< orphan*/  DFLL_DROOP_CTRL ; 
 int /*<<< orphan*/  DFLL_MONITOR_CTRL ; 
 int DFLL_MONITOR_CTRL_FREQ ; 
 int /*<<< orphan*/  DFLL_PARAMS ; 
 int DFLL_PARAMS_CF_PARAM_SHIFT ; 
 int DFLL_PARAMS_CG_PARAM_SHIFT ; 
 int DFLL_PARAMS_CG_SCALE ; 
 int DFLL_PARAMS_CI_PARAM_SHIFT ; 
 int DFLL_PARAMS_FORCE_MODE_SHIFT ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dfll_tune_low (struct tegra_dfll*) ; 
 int /*<<< orphan*/  dfll_writel (struct tegra_dfll*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dfll_set_default_params(struct tegra_dfll *td)
{
	u32 val;

	val = DIV_ROUND_UP(td->ref_rate, td->sample_rate * 32);
	BUG_ON(val > DFLL_CONFIG_DIV_MASK);
	dfll_writel(td, val, DFLL_CONFIG);

	val = (td->force_mode << DFLL_PARAMS_FORCE_MODE_SHIFT) |
		(td->cf << DFLL_PARAMS_CF_PARAM_SHIFT) |
		(td->ci << DFLL_PARAMS_CI_PARAM_SHIFT) |
		(td->cg << DFLL_PARAMS_CG_PARAM_SHIFT) |
		(td->cg_scale ? DFLL_PARAMS_CG_SCALE : 0);
	dfll_writel(td, val, DFLL_PARAMS);

	dfll_tune_low(td);
	dfll_writel(td, td->droop_ctrl, DFLL_DROOP_CTRL);
	dfll_writel(td, DFLL_MONITOR_CTRL_FREQ, DFLL_MONITOR_CTRL);
}