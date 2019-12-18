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
typedef  int /*<<< orphan*/  u32 ;
struct tegra_pmx {TYPE_1__* soc; } ;
struct tegra_pingroup {int mux_reg; unsigned int mux_bank; unsigned int drv_bank; unsigned int drv_reg; int /*<<< orphan*/  parked_bitmask; } ;
struct TYPE_2__ {int ngroups; struct tegra_pingroup* groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmx_readl (struct tegra_pmx*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pmx_writel (struct tegra_pmx*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static void tegra_pinctrl_clear_parked_bits(struct tegra_pmx *pmx)
{
	int i = 0;
	const struct tegra_pingroup *g;
	u32 val;

	for (i = 0; i < pmx->soc->ngroups; ++i) {
		g = &pmx->soc->groups[i];
		if (g->parked_bitmask > 0) {
			unsigned int bank, reg;

			if (g->mux_reg != -1) {
				bank = g->mux_bank;
				reg = g->mux_reg;
			} else {
				bank = g->drv_bank;
				reg = g->drv_reg;
			}

			val = pmx_readl(pmx, bank, reg);
			val &= ~g->parked_bitmask;
			pmx_writel(pmx, val, bank, reg);
		}
	}
}