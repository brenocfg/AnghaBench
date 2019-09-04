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
struct pic32_sys_pll_data {int /*<<< orphan*/  lock_mask; scalar_t__ status_reg; scalar_t__ ctrl_reg; int /*<<< orphan*/  init_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * init; } ;
struct pic32_sys_pll {int idiv; TYPE_1__ hw; scalar_t__ ctrl_reg; int /*<<< orphan*/  lock_mask; scalar_t__ status_reg; struct pic32_clk_common* core; } ;
struct pic32_clk_common {int /*<<< orphan*/  dev; scalar_t__ iobase; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PLL_IDIV_MASK ; 
 int PLL_IDIV_SHIFT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct clk* devm_clk_register (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct pic32_sys_pll* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

struct clk *pic32_spll_clk_register(const struct pic32_sys_pll_data *data,
				    struct pic32_clk_common *core)
{
	struct pic32_sys_pll *spll;
	struct clk *clk;

	spll = devm_kzalloc(core->dev, sizeof(*spll), GFP_KERNEL);
	if (!spll)
		return ERR_PTR(-ENOMEM);

	spll->core = core;
	spll->hw.init = &data->init_data;
	spll->ctrl_reg = data->ctrl_reg + core->iobase;
	spll->status_reg = data->status_reg + core->iobase;
	spll->lock_mask = data->lock_mask;

	/* cache PLL idiv; PLL driver uses it as constant.*/
	spll->idiv = (readl(spll->ctrl_reg) >> PLL_IDIV_SHIFT) & PLL_IDIV_MASK;
	spll->idiv += 1;

	clk = devm_clk_register(core->dev, &spll->hw);
	if (IS_ERR(clk))
		dev_err(core->dev, "sys_pll: clk_register() failed\n");

	return clk;
}