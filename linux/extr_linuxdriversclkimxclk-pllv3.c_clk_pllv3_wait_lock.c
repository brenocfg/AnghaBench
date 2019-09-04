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
typedef  int u32 ;
struct clk_pllv3 {int power_bit; int /*<<< orphan*/  base; scalar_t__ powerup_set; } ;

/* Variables and functions */
 int BM_PLL_LOCK ; 
 int ETIMEDOUT ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int clk_pllv3_wait_lock(struct clk_pllv3 *pll)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(10);
	u32 val = readl_relaxed(pll->base) & pll->power_bit;

	/* No need to wait for lock when pll is not powered up */
	if ((pll->powerup_set && !val) || (!pll->powerup_set && val))
		return 0;

	/* Wait for PLL to lock */
	do {
		if (readl_relaxed(pll->base) & BM_PLL_LOCK)
			break;
		if (time_after(jiffies, timeout))
			break;
		usleep_range(50, 500);
	} while (1);

	return readl_relaxed(pll->base) & BM_PLL_LOCK ? 0 : -ETIMEDOUT;
}