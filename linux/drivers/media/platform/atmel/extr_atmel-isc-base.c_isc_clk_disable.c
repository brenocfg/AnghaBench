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
struct isc_clk {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; int /*<<< orphan*/  id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_CLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_CLKDIS ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct isc_clk* to_isc_clk (struct clk_hw*) ; 

__attribute__((used)) static void isc_clk_disable(struct clk_hw *hw)
{
	struct isc_clk *isc_clk = to_isc_clk(hw);
	u32 id = isc_clk->id;
	unsigned long flags;

	spin_lock_irqsave(&isc_clk->lock, flags);
	regmap_write(isc_clk->regmap, ISC_CLKDIS, ISC_CLK(id));
	spin_unlock_irqrestore(&isc_clk->lock, flags);
}