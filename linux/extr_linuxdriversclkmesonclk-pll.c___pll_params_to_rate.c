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
typedef  int u64 ;
typedef  int u16 ;
struct pll_rate_table {int m; unsigned int od; unsigned int od2; unsigned int od3; unsigned int n; } ;
struct TYPE_2__ {int width; } ;
struct meson_clk_pll_data {TYPE_1__ frac; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP_ULL (int,unsigned int) ; 
 scalar_t__ MESON_PARM_APPLICABLE (TYPE_1__*) ; 

__attribute__((used)) static unsigned long __pll_params_to_rate(unsigned long parent_rate,
					  const struct pll_rate_table *pllt,
					  u16 frac,
					  struct meson_clk_pll_data *pll)
{
	u64 rate = (u64)parent_rate * pllt->m;
	unsigned int od = pllt->od + pllt->od2 + pllt->od3;

	if (frac && MESON_PARM_APPLICABLE(&pll->frac)) {
		u64 frac_rate = (u64)parent_rate * frac;

		rate += DIV_ROUND_UP_ULL(frac_rate,
					 (1 << pll->frac.width));
	}

	return DIV_ROUND_UP_ULL(rate, pllt->n << od);
}