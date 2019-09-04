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
struct st_clk_quadfs_pll {int ndiv; TYPE_1__* data; scalar_t__ lock; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {scalar_t__ lockstatus_present; int /*<<< orphan*/  powerup_polarity; scalar_t__ bwfilter_present; scalar_t__ reset_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKGEN_READ (struct st_clk_quadfs_pll*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLKGEN_WRITE (struct st_clk_quadfs_pll*,int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 
 int PLL_BW_GOODREF ; 
 int /*<<< orphan*/  cpu_relax () ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  lock_status ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  ndiv ; 
 int /*<<< orphan*/  npda ; 
 int /*<<< orphan*/  nreset ; 
 int /*<<< orphan*/  ref_bw ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 struct st_clk_quadfs_pll* to_quadfs_pll (struct clk_hw*) ; 

__attribute__((used)) static int quadfs_pll_enable(struct clk_hw *hw)
{
	struct st_clk_quadfs_pll *pll = to_quadfs_pll(hw);
	unsigned long flags = 0, timeout = jiffies + msecs_to_jiffies(10);

	if (pll->lock)
		spin_lock_irqsave(pll->lock, flags);

	/*
	 * Bring block out of reset if we have reset control.
	 */
	if (pll->data->reset_present)
		CLKGEN_WRITE(pll, nreset, 1);

	/*
	 * Use a fixed input clock noise bandwidth filter for the moment
	 */
	if (pll->data->bwfilter_present)
		CLKGEN_WRITE(pll, ref_bw, PLL_BW_GOODREF);


	CLKGEN_WRITE(pll, ndiv, pll->ndiv);

	/*
	 * Power up the PLL
	 */
	CLKGEN_WRITE(pll, npda, !pll->data->powerup_polarity);

	if (pll->lock)
		spin_unlock_irqrestore(pll->lock, flags);

	if (pll->data->lockstatus_present)
		while (!CLKGEN_READ(pll, lock_status)) {
			if (time_after(jiffies, timeout))
				return -ETIMEDOUT;
			cpu_relax();
		}

	return 0;
}