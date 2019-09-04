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
struct clk_hw {int dummy; } ;
struct clk_generated {int id; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT91_PMC_PCR ; 
 int AT91_PMC_PCR_CMD ; 
 int AT91_PMC_PCR_GCKEN ; 
 int AT91_PMC_PCR_PID_MASK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_generated* to_clk_generated (struct clk_hw*) ; 

__attribute__((used)) static void clk_generated_disable(struct clk_hw *hw)
{
	struct clk_generated *gck = to_clk_generated(hw);
	unsigned long flags;

	spin_lock_irqsave(gck->lock, flags);
	regmap_write(gck->regmap, AT91_PMC_PCR,
		     (gck->id & AT91_PMC_PCR_PID_MASK));
	regmap_update_bits(gck->regmap, AT91_PMC_PCR,
			   AT91_PMC_PCR_CMD | AT91_PMC_PCR_GCKEN,
			   AT91_PMC_PCR_CMD);
	spin_unlock_irqrestore(gck->lock, flags);
}