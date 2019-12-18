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
struct ti_pipe3 {int /*<<< orphan*/  dev; int /*<<< orphan*/  pll_ctrl_base; } ;

/* Variables and functions */
 int EBUSY ; 
 int PLL_LOCK ; 
 int /*<<< orphan*/  PLL_LOCK_TIME ; 
 int /*<<< orphan*/  PLL_STATUS ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int ti_pipe3_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int ti_pipe3_dpll_wait_lock(struct ti_pipe3 *phy)
{
	u32		val;
	unsigned long	timeout;

	timeout = jiffies + msecs_to_jiffies(PLL_LOCK_TIME);
	do {
		cpu_relax();
		val = ti_pipe3_readl(phy->pll_ctrl_base, PLL_STATUS);
		if (val & PLL_LOCK)
			return 0;
	} while (!time_after(jiffies, timeout));

	dev_err(phy->dev, "DPLL failed to lock\n");
	return -EBUSY;
}