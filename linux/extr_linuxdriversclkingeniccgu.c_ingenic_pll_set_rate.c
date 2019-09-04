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
typedef  unsigned int u32 ;
struct ingenic_clk {struct ingenic_cgu* cgu; } ;
struct ingenic_cgu_pll_info {unsigned int m_shift; unsigned int m_offset; unsigned int n_shift; unsigned int n_offset; unsigned int od_shift; unsigned int* od_encoding; scalar_t__ reg; scalar_t__ od_bits; scalar_t__ n_bits; scalar_t__ m_bits; } ;
struct ingenic_cgu_clk_info {int /*<<< orphan*/  name; struct ingenic_cgu_pll_info pll; } ;
struct ingenic_cgu {int /*<<< orphan*/  lock; scalar_t__ base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long ingenic_pll_calc (struct ingenic_cgu_clk_info const*,unsigned long,unsigned long,unsigned int*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ingenic_cgu_clk_info* to_clk_info (struct ingenic_clk*) ; 
 struct ingenic_clk* to_ingenic_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int
ingenic_pll_set_rate(struct clk_hw *hw, unsigned long req_rate,
		     unsigned long parent_rate)
{
	struct ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	struct ingenic_cgu *cgu = ingenic_clk->cgu;
	const struct ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);
	const struct ingenic_cgu_pll_info *pll_info = &clk_info->pll;
	unsigned long rate, flags;
	unsigned int m, n, od;
	u32 ctl;

	rate = ingenic_pll_calc(clk_info, req_rate, parent_rate,
			       &m, &n, &od);
	if (rate != req_rate)
		pr_info("ingenic-cgu: request '%s' rate %luHz, actual %luHz\n",
			clk_info->name, req_rate, rate);

	spin_lock_irqsave(&cgu->lock, flags);
	ctl = readl(cgu->base + pll_info->reg);

	ctl &= ~(GENMASK(pll_info->m_bits - 1, 0) << pll_info->m_shift);
	ctl |= (m - pll_info->m_offset) << pll_info->m_shift;

	ctl &= ~(GENMASK(pll_info->n_bits - 1, 0) << pll_info->n_shift);
	ctl |= (n - pll_info->n_offset) << pll_info->n_shift;

	ctl &= ~(GENMASK(pll_info->od_bits - 1, 0) << pll_info->od_shift);
	ctl |= pll_info->od_encoding[od - 1] << pll_info->od_shift;

	writel(ctl, cgu->base + pll_info->reg);
	spin_unlock_irqrestore(&cgu->lock, flags);

	return 0;
}