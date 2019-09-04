#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  max_pix_clk_freq_hz; int /*<<< orphan*/  min_pix_clk_freq_hz; int /*<<< orphan*/  max_sys_clk_freq_hz; int /*<<< orphan*/  min_sys_clk_freq_hz; } ;
struct smiapp_pll_limits {TYPE_2__ vt; int /*<<< orphan*/  max_pll_op_freq_hz; int /*<<< orphan*/  min_pll_op_freq_hz; int /*<<< orphan*/  max_pll_multiplier; int /*<<< orphan*/  min_pll_multiplier; int /*<<< orphan*/  max_pll_ip_freq_hz; int /*<<< orphan*/  min_pll_ip_freq_hz; } ;
struct smiapp_pll_branch_limits {int /*<<< orphan*/  max_pix_clk_freq_hz; int /*<<< orphan*/  min_pix_clk_freq_hz; int /*<<< orphan*/  max_sys_clk_freq_hz; int /*<<< orphan*/  min_sys_clk_freq_hz; int /*<<< orphan*/  max_sys_clk_div; int /*<<< orphan*/  min_sys_clk_div; } ;
struct smiapp_pll_branch {int /*<<< orphan*/  pix_clk_freq_hz; int /*<<< orphan*/  sys_clk_freq_hz; int /*<<< orphan*/  sys_clk_div; } ;
struct TYPE_3__ {int /*<<< orphan*/  pix_clk_freq_hz; int /*<<< orphan*/  sys_clk_freq_hz; } ;
struct smiapp_pll {int flags; TYPE_1__ vt; int /*<<< orphan*/  pll_op_clk_freq_hz; int /*<<< orphan*/  pll_multiplier; int /*<<< orphan*/  pll_ip_clk_freq_hz; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SMIAPP_PLL_FLAG_NO_OP_CLOCKS ; 
 int bounds_check (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_all_bounds(struct device *dev,
			    const struct smiapp_pll_limits *limits,
			    const struct smiapp_pll_branch_limits *op_limits,
			    struct smiapp_pll *pll,
			    struct smiapp_pll_branch *op_pll)
{
	int rval;

	rval = bounds_check(dev, pll->pll_ip_clk_freq_hz,
			    limits->min_pll_ip_freq_hz,
			    limits->max_pll_ip_freq_hz,
			    "pll_ip_clk_freq_hz");
	if (!rval)
		rval = bounds_check(
			dev, pll->pll_multiplier,
			limits->min_pll_multiplier, limits->max_pll_multiplier,
			"pll_multiplier");
	if (!rval)
		rval = bounds_check(
			dev, pll->pll_op_clk_freq_hz,
			limits->min_pll_op_freq_hz, limits->max_pll_op_freq_hz,
			"pll_op_clk_freq_hz");
	if (!rval)
		rval = bounds_check(
			dev, op_pll->sys_clk_div,
			op_limits->min_sys_clk_div, op_limits->max_sys_clk_div,
			"op_sys_clk_div");
	if (!rval)
		rval = bounds_check(
			dev, op_pll->sys_clk_freq_hz,
			op_limits->min_sys_clk_freq_hz,
			op_limits->max_sys_clk_freq_hz,
			"op_sys_clk_freq_hz");
	if (!rval)
		rval = bounds_check(
			dev, op_pll->pix_clk_freq_hz,
			op_limits->min_pix_clk_freq_hz,
			op_limits->max_pix_clk_freq_hz,
			"op_pix_clk_freq_hz");

	/*
	 * If there are no OP clocks, the VT clocks are contained in
	 * the OP clock struct.
	 */
	if (pll->flags & SMIAPP_PLL_FLAG_NO_OP_CLOCKS)
		return rval;

	if (!rval)
		rval = bounds_check(
			dev, pll->vt.sys_clk_freq_hz,
			limits->vt.min_sys_clk_freq_hz,
			limits->vt.max_sys_clk_freq_hz,
			"vt_sys_clk_freq_hz");
	if (!rval)
		rval = bounds_check(
			dev, pll->vt.pix_clk_freq_hz,
			limits->vt.min_pix_clk_freq_hz,
			limits->vt.max_pix_clk_freq_hz,
			"vt_pix_clk_freq_hz");

	return rval;
}