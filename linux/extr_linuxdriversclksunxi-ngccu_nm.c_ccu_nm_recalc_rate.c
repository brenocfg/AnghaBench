#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_9__ {int features; scalar_t__ reg; scalar_t__ base; } ;
struct TYPE_8__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct TYPE_7__ {unsigned long shift; int width; scalar_t__ offset; } ;
struct ccu_nm {unsigned long fixed_post_div; TYPE_3__ common; int /*<<< orphan*/  sdm; TYPE_2__ m; TYPE_1__ n; int /*<<< orphan*/  frac; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 scalar_t__ ccu_frac_helper_is_enabled (TYPE_3__*,int /*<<< orphan*/ *) ; 
 unsigned long ccu_frac_helper_read_rate (TYPE_3__*,int /*<<< orphan*/ *) ; 
 unsigned long ccu_nm_calc_rate (unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ ccu_sdm_helper_is_enabled (TYPE_3__*,int /*<<< orphan*/ *) ; 
 unsigned long ccu_sdm_helper_read_rate (TYPE_3__*,int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 struct ccu_nm* hw_to_ccu_nm (struct clk_hw*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long ccu_nm_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct ccu_nm *nm = hw_to_ccu_nm(hw);
	unsigned long rate;
	unsigned long n, m;
	u32 reg;

	if (ccu_frac_helper_is_enabled(&nm->common, &nm->frac)) {
		rate = ccu_frac_helper_read_rate(&nm->common, &nm->frac);

		if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
			rate /= nm->fixed_post_div;

		return rate;
	}

	reg = readl(nm->common.base + nm->common.reg);

	n = reg >> nm->n.shift;
	n &= (1 << nm->n.width) - 1;
	n += nm->n.offset;
	if (!n)
		n++;

	m = reg >> nm->m.shift;
	m &= (1 << nm->m.width) - 1;
	m += nm->m.offset;
	if (!m)
		m++;

	if (ccu_sdm_helper_is_enabled(&nm->common, &nm->sdm))
		rate = ccu_sdm_helper_read_rate(&nm->common, &nm->sdm, m, n);
	else
		rate = ccu_nm_calc_rate(parent_rate, n, m);

	if (nm->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= nm->fixed_post_div;

	return rate;
}