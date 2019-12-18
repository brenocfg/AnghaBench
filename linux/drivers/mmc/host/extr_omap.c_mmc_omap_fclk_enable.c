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
struct mmc_omap_host {unsigned int fclk_enabled; int /*<<< orphan*/  clk_lock; int /*<<< orphan*/  fclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mmc_omap_fclk_enable(struct mmc_omap_host *host, unsigned int enable)
{
	unsigned long flags;

	spin_lock_irqsave(&host->clk_lock, flags);
	if (host->fclk_enabled != enable) {
		host->fclk_enabled = enable;
		if (enable)
			clk_enable(host->fclk);
		else
			clk_disable(host->fclk);
	}
	spin_unlock_irqrestore(&host->clk_lock, flags);
}