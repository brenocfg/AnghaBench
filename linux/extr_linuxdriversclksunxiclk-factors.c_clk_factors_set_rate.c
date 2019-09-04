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
typedef  int /*<<< orphan*/  u32 ;
struct factors_request {unsigned long rate; unsigned long parent_rate; int /*<<< orphan*/  p; int /*<<< orphan*/  m; int /*<<< orphan*/  k; int /*<<< orphan*/  n; } ;
struct clk_hw {int dummy; } ;
struct clk_factors_config {int /*<<< orphan*/  pwidth; int /*<<< orphan*/  pshift; int /*<<< orphan*/  mwidth; int /*<<< orphan*/  mshift; int /*<<< orphan*/  kwidth; int /*<<< orphan*/  kshift; int /*<<< orphan*/  nwidth; int /*<<< orphan*/  nshift; } ;
struct clk_factors {scalar_t__ lock; int /*<<< orphan*/  reg; int /*<<< orphan*/  (* get_factors ) (struct factors_request*) ;struct clk_factors_config* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  FACTOR_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __delay (unsigned long) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct factors_request*) ; 
 struct clk_factors* to_clk_factors (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_factors_set_rate(struct clk_hw *hw, unsigned long rate,
				unsigned long parent_rate)
{
	struct factors_request req = {
		.rate = rate,
		.parent_rate = parent_rate,
	};
	u32 reg;
	struct clk_factors *factors = to_clk_factors(hw);
	const struct clk_factors_config *config = factors->config;
	unsigned long flags = 0;

	factors->get_factors(&req);

	if (factors->lock)
		spin_lock_irqsave(factors->lock, flags);

	/* Fetch the register value */
	reg = readl(factors->reg);

	/* Set up the new factors - macros do not do anything if width is 0 */
	reg = FACTOR_SET(config->nshift, config->nwidth, reg, req.n);
	reg = FACTOR_SET(config->kshift, config->kwidth, reg, req.k);
	reg = FACTOR_SET(config->mshift, config->mwidth, reg, req.m);
	reg = FACTOR_SET(config->pshift, config->pwidth, reg, req.p);

	/* Apply them now */
	writel(reg, factors->reg);

	/* delay 500us so pll stabilizes */
	__delay((rate >> 20) * 500 / 2);

	if (factors->lock)
		spin_unlock_irqrestore(factors->lock, flags);

	return 0;
}