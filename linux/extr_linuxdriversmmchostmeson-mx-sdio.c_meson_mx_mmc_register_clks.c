#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct clk_init_data* init; } ;
struct TYPE_5__ {TYPE_3__ hw; int /*<<< orphan*/  flags; int /*<<< orphan*/  width; int /*<<< orphan*/  shift; scalar_t__ reg; } ;
struct TYPE_4__ {int div; int mult; TYPE_3__ hw; } ;
struct meson_mx_mmc_host {void* cfg_div_clk; TYPE_2__ cfg_div; int /*<<< orphan*/  controller_dev; scalar_t__ base; void* fixed_factor_clk; TYPE_1__ fixed_factor; void* parent_clk; } ;
struct clk_init_data {char const** parent_names; int num_parents; scalar_t__ flags; int /*<<< orphan*/ * ops; void* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_DIVIDER_ALLOW_ZERO ; 
 scalar_t__ CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (void*) ; 
 scalar_t__ MESON_MX_SDIO_CONF ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF_CMD_CLK_DIV_SHIFT ; 
 int /*<<< orphan*/  MESON_MX_SDIO_CONF_CMD_CLK_DIV_WIDTH ; 
 int PTR_ERR (void*) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 char* __clk_get_name (void*) ; 
 int /*<<< orphan*/  clk_divider_ops ; 
 int /*<<< orphan*/  clk_fixed_factor_ops ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 void* devm_clk_register (int /*<<< orphan*/ ,TYPE_3__*) ; 
 void* devm_kasprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_mx_mmc_register_clks(struct meson_mx_mmc_host *host)
{
	struct clk_init_data init;
	const char *clk_div_parent, *clk_fixed_factor_parent;

	clk_fixed_factor_parent = __clk_get_name(host->parent_clk);
	init.name = devm_kasprintf(host->controller_dev, GFP_KERNEL,
				   "%s#fixed_factor",
				   dev_name(host->controller_dev));
	if (!init.name)
		return -ENOMEM;

	init.ops = &clk_fixed_factor_ops;
	init.flags = 0;
	init.parent_names = &clk_fixed_factor_parent;
	init.num_parents = 1;
	host->fixed_factor.div = 2;
	host->fixed_factor.mult = 1;
	host->fixed_factor.hw.init = &init;

	host->fixed_factor_clk = devm_clk_register(host->controller_dev,
						 &host->fixed_factor.hw);
	if (WARN_ON(IS_ERR(host->fixed_factor_clk)))
		return PTR_ERR(host->fixed_factor_clk);

	clk_div_parent = __clk_get_name(host->fixed_factor_clk);
	init.name = devm_kasprintf(host->controller_dev, GFP_KERNEL,
				   "%s#div", dev_name(host->controller_dev));
	if (!init.name)
		return -ENOMEM;

	init.ops = &clk_divider_ops;
	init.flags = CLK_SET_RATE_PARENT;
	init.parent_names = &clk_div_parent;
	init.num_parents = 1;
	host->cfg_div.reg = host->base + MESON_MX_SDIO_CONF;
	host->cfg_div.shift = MESON_MX_SDIO_CONF_CMD_CLK_DIV_SHIFT;
	host->cfg_div.width = MESON_MX_SDIO_CONF_CMD_CLK_DIV_WIDTH;
	host->cfg_div.hw.init = &init;
	host->cfg_div.flags = CLK_DIVIDER_ALLOW_ZERO;

	host->cfg_div_clk = devm_clk_register(host->controller_dev,
					      &host->cfg_div.hw);
	if (WARN_ON(IS_ERR(host->cfg_div_clk)))
		return PTR_ERR(host->cfg_div_clk);

	return 0;
}