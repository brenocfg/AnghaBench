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
typedef  struct pll_rate_table {unsigned long rate; } const pll_rate_table ;
struct meson_clk_pll_data {int flags; int /*<<< orphan*/  frac; struct pll_rate_table const* table; } ;

/* Variables and functions */
 int CLK_MESON_PLL_ROUND_CLOSEST ; 
 scalar_t__ MESON_PARM_APPLICABLE (int /*<<< orphan*/ *) ; 
 scalar_t__ abs (unsigned long) ; 

__attribute__((used)) static const struct pll_rate_table *
meson_clk_get_pll_settings(unsigned long rate,
			   struct meson_clk_pll_data *pll)
{
	const struct pll_rate_table *table = pll->table;
	unsigned int i = 0;

	if (!table)
		return NULL;

	/* Find the first table element exceeding rate */
	while (table[i].rate && table[i].rate <= rate)
		i++;

	if (i != 0) {
		if (MESON_PARM_APPLICABLE(&pll->frac) ||
		    !(pll->flags & CLK_MESON_PLL_ROUND_CLOSEST) ||
		    (abs(rate - table[i - 1].rate) <
		     abs(rate - table[i].rate)))
			i--;
	}

	return (struct pll_rate_table *)&table[i];
}