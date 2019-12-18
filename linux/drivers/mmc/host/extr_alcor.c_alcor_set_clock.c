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
typedef  int u8 ;
typedef  int u16 ;
struct alcor_sdmmc_host {int /*<<< orphan*/  dev; struct alcor_pci_priv* alcor_pci; } ;
struct alcor_pll_conf {unsigned int min_div; unsigned int max_div; int clk_src_reg; int /*<<< orphan*/  clk_src_freq; } ;
struct alcor_pci_priv {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct alcor_pll_conf*) ; 
 int AU6601_CLK_ENABLE ; 
 int /*<<< orphan*/  AU6601_CLK_SELECT ; 
 void* DIV_ROUND_UP (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int abs (unsigned int) ; 
 struct alcor_pll_conf* alcor_pll_cfg ; 
 int /*<<< orphan*/  alcor_write16 (struct alcor_pci_priv*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,unsigned int,int,int,int) ; 

__attribute__((used)) static void alcor_set_clock(struct alcor_sdmmc_host *host, unsigned int clock)
{
	struct alcor_pci_priv *priv = host->alcor_pci;
	int i, diff = 0x7fffffff, tmp_clock = 0;
	u16 clk_src = 0;
	u8 clk_div = 0;

	if (clock == 0) {
		alcor_write16(priv, 0, AU6601_CLK_SELECT);
		return;
	}

	for (i = 0; i < ARRAY_SIZE(alcor_pll_cfg); i++) {
		unsigned int tmp_div, tmp_diff;
		const struct alcor_pll_conf *cfg = &alcor_pll_cfg[i];

		tmp_div = DIV_ROUND_UP(cfg->clk_src_freq, clock);
		if (cfg->min_div > tmp_div || tmp_div > cfg->max_div)
			continue;

		tmp_clock = DIV_ROUND_UP(cfg->clk_src_freq, tmp_div);
		tmp_diff = abs(clock - tmp_clock);

		if (tmp_diff < diff) {
			diff = tmp_diff;
			clk_src = cfg->clk_src_reg;
			clk_div = tmp_div;
		}
	}

	clk_src |= ((clk_div - 1) << 8);
	clk_src |= AU6601_CLK_ENABLE;

	dev_dbg(host->dev, "set freq %d cal freq %d, use div %d, mod %x\n",
			clock, tmp_clock, clk_div, clk_src);

	alcor_write16(priv, clk_src, AU6601_CLK_SELECT);

}