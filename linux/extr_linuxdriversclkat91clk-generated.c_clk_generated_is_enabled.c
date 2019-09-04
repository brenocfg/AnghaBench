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
 unsigned int AT91_PMC_PCR_GCKEN ; 
 int AT91_PMC_PCR_PID_MASK ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_generated* to_clk_generated (struct clk_hw*) ; 

__attribute__((used)) static int clk_generated_is_enabled(struct clk_hw *hw)
{
	struct clk_generated *gck = to_clk_generated(hw);
	unsigned long flags;
	unsigned int status;

	spin_lock_irqsave(gck->lock, flags);
	regmap_write(gck->regmap, AT91_PMC_PCR,
		     (gck->id & AT91_PMC_PCR_PID_MASK));
	regmap_read(gck->regmap, AT91_PMC_PCR, &status);
	spin_unlock_irqrestore(gck->lock, flags);

	return status & AT91_PMC_PCR_GCKEN ? 1 : 0;
}