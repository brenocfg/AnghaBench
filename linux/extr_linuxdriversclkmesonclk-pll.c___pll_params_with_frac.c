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
struct pll_rate_table {int n; int od; int od2; int od3; int m; } ;
struct TYPE_2__ {int width; } ;
struct meson_clk_pll_data {int flags; TYPE_1__ frac; } ;

/* Variables and functions */
 int CLK_MESON_PLL_ROUND_CLOSEST ; 
 int DIV_ROUND_CLOSEST_ULL (int,unsigned long) ; 
 int div_u64 (int,unsigned long) ; 
 int min (int,int) ; 

__attribute__((used)) static u16 __pll_params_with_frac(unsigned long rate,
				  unsigned long parent_rate,
				  const struct pll_rate_table *pllt,
				  struct meson_clk_pll_data *pll)
{
	u16 frac_max = (1 << pll->frac.width);
	u64 val = (u64)rate * pllt->n;

	val <<= pllt->od + pllt->od2 + pllt->od3;

	if (pll->flags & CLK_MESON_PLL_ROUND_CLOSEST)
		val = DIV_ROUND_CLOSEST_ULL(val * frac_max, parent_rate);
	else
		val = div_u64(val * frac_max, parent_rate);

	val -= pllt->m * frac_max;

	return min((u16)val, (u16)(frac_max - 1));
}