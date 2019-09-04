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
struct TYPE_4__ {int /*<<< orphan*/  pix_clk_freq_hz; int /*<<< orphan*/  sys_clk_freq_hz; int /*<<< orphan*/  pix_clk_div; int /*<<< orphan*/  sys_clk_div; } ;
struct TYPE_3__ {int /*<<< orphan*/  pix_clk_freq_hz; int /*<<< orphan*/  sys_clk_freq_hz; int /*<<< orphan*/  pix_clk_div; int /*<<< orphan*/  sys_clk_div; } ;
struct smiapp_pll {int flags; TYPE_2__ vt; TYPE_1__ op; int /*<<< orphan*/  pll_op_clk_freq_hz; int /*<<< orphan*/  pll_ip_clk_freq_hz; int /*<<< orphan*/  ext_clk_freq_hz; int /*<<< orphan*/  pll_multiplier; int /*<<< orphan*/  pre_pll_clk_div; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SMIAPP_PLL_FLAG_NO_OP_CLOCKS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_pll(struct device *dev, struct smiapp_pll *pll)
{
	dev_dbg(dev, "pre_pll_clk_div\t%u\n",  pll->pre_pll_clk_div);
	dev_dbg(dev, "pll_multiplier \t%u\n",  pll->pll_multiplier);
	if (!(pll->flags & SMIAPP_PLL_FLAG_NO_OP_CLOCKS)) {
		dev_dbg(dev, "op_sys_clk_div \t%u\n", pll->op.sys_clk_div);
		dev_dbg(dev, "op_pix_clk_div \t%u\n", pll->op.pix_clk_div);
	}
	dev_dbg(dev, "vt_sys_clk_div \t%u\n",  pll->vt.sys_clk_div);
	dev_dbg(dev, "vt_pix_clk_div \t%u\n",  pll->vt.pix_clk_div);

	dev_dbg(dev, "ext_clk_freq_hz \t%u\n", pll->ext_clk_freq_hz);
	dev_dbg(dev, "pll_ip_clk_freq_hz \t%u\n", pll->pll_ip_clk_freq_hz);
	dev_dbg(dev, "pll_op_clk_freq_hz \t%u\n", pll->pll_op_clk_freq_hz);
	if (!(pll->flags & SMIAPP_PLL_FLAG_NO_OP_CLOCKS)) {
		dev_dbg(dev, "op_sys_clk_freq_hz \t%u\n",
			pll->op.sys_clk_freq_hz);
		dev_dbg(dev, "op_pix_clk_freq_hz \t%u\n",
			pll->op.pix_clk_freq_hz);
	}
	dev_dbg(dev, "vt_sys_clk_freq_hz \t%u\n", pll->vt.sys_clk_freq_hz);
	dev_dbg(dev, "vt_pix_clk_freq_hz \t%u\n", pll->vt.pix_clk_freq_hz);
}