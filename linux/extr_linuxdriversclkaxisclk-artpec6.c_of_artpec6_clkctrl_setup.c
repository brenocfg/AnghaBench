#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;
struct TYPE_4__ {int clk_num; struct clk** clks; } ;
struct TYPE_5__ {TYPE_1__ clk_data; struct clk** clk_table; int /*<<< orphan*/ * syscon_base; } ;

/* Variables and functions */
 size_t ARTPEC6_CLK_CPU ; 
 size_t ARTPEC6_CLK_CPU_PERIPH ; 
 size_t ARTPEC6_CLK_DBG_PCLK ; 
 int ARTPEC6_CLK_NUMCLOCKS ; 
 size_t ARTPEC6_CLK_SPI_PCLK ; 
 size_t ARTPEC6_CLK_SPI_SSPCLK ; 
 size_t ARTPEC6_CLK_UART_PCLK ; 
 size_t ARTPEC6_CLK_UART_REFCLK ; 
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct clk* clk_register_fixed_factor (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int,int) ; 
 struct clk* clk_register_fixed_rate (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* clkdata ; 
 TYPE_2__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* of_clk_get_parent_name (struct device_node*,int) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 
 int /*<<< orphan*/ * of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_property_match_string (struct device_node*,char*,char*) ; 
 int readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void of_artpec6_clkctrl_setup(struct device_node *np)
{
	int i;
	const char *sys_refclk_name;
	u32 pll_mode, pll_m, pll_n;
	struct clk **clks;

	/* Mandatory parent clock. */
	i = of_property_match_string(np, "clock-names", "sys_refclk");
	if (i < 0)
		return;

	sys_refclk_name = of_clk_get_parent_name(np, i);

	clkdata = kzalloc(sizeof(*clkdata), GFP_KERNEL);
	if (!clkdata)
		return;

	clks = clkdata->clk_table;

	for (i = 0; i < ARTPEC6_CLK_NUMCLOCKS; ++i)
		clks[i] = ERR_PTR(-EPROBE_DEFER);

	clkdata->syscon_base = of_iomap(np, 0);
	BUG_ON(clkdata->syscon_base == NULL);

	/* Read PLL1 factors configured by boot strap pins. */
	pll_mode = (readl(clkdata->syscon_base) >> 6) & 3;
	switch (pll_mode) {
	case 0:		/* DDR3-2133 mode */
		pll_m = 4;
		pll_n = 85;
		break;
	case 1:		/* DDR3-1866 mode */
		pll_m = 6;
		pll_n = 112;
		break;
	case 2:		/* DDR3-1600 mode */
		pll_m = 4;
		pll_n = 64;
		break;
	case 3:		/* DDR3-1333 mode */
		pll_m = 8;
		pll_n = 106;
		break;
	}

	clks[ARTPEC6_CLK_CPU] =
	    clk_register_fixed_factor(NULL, "cpu", sys_refclk_name, 0, pll_n,
				      pll_m);
	clks[ARTPEC6_CLK_CPU_PERIPH] =
	    clk_register_fixed_factor(NULL, "cpu_periph", "cpu", 0, 1, 2);

	/* EPROBE_DEFER on the apb_clock is not handled in amba devices. */
	clks[ARTPEC6_CLK_UART_PCLK] =
	    clk_register_fixed_factor(NULL, "uart_pclk", "cpu", 0, 1, 8);
	clks[ARTPEC6_CLK_UART_REFCLK] =
	    clk_register_fixed_rate(NULL, "uart_ref", sys_refclk_name, 0,
				    50000000);

	clks[ARTPEC6_CLK_SPI_PCLK] =
	    clk_register_fixed_factor(NULL, "spi_pclk", "cpu", 0, 1, 8);
	clks[ARTPEC6_CLK_SPI_SSPCLK] =
	    clk_register_fixed_rate(NULL, "spi_sspclk", sys_refclk_name, 0,
				    50000000);

	clks[ARTPEC6_CLK_DBG_PCLK] =
	    clk_register_fixed_factor(NULL, "dbg_pclk", "cpu", 0, 1, 8);

	clkdata->clk_data.clks = clkdata->clk_table;
	clkdata->clk_data.clk_num = ARTPEC6_CLK_NUMCLOCKS;

	of_clk_add_provider(np, of_clk_src_onecell_get, &clkdata->clk_data);
}