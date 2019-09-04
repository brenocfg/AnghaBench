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

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_DPI_CLOCK_SETTING ; 
 int /*<<< orphan*/  PRCMU_DSI_CLOCK_SETTING ; 
 int /*<<< orphan*/  PRCMU_DSI_LP_CLOCK_SETTING ; 
 scalar_t__ PRCM_HDMICLK_MGT ; 
 scalar_t__ PRCM_LCDCLK_MGT ; 
 scalar_t__ PRCM_SEM ; 
 int PRCM_SEM_PRCM_SEM ; 
 scalar_t__ PRCM_TVCLK_MGT ; 
 int /*<<< orphan*/  clk_mgt_lock ; 
 int /*<<< orphan*/  cpu_relax () ; 
 scalar_t__ prcmu_base ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int db8500_prcmu_set_display_clocks(void)
{
	unsigned long flags;

	spin_lock_irqsave(&clk_mgt_lock, flags);

	/* Grab the HW semaphore. */
	while ((readl(PRCM_SEM) & PRCM_SEM_PRCM_SEM) != 0)
		cpu_relax();

	writel(PRCMU_DSI_CLOCK_SETTING, prcmu_base + PRCM_HDMICLK_MGT);
	writel(PRCMU_DSI_LP_CLOCK_SETTING, prcmu_base + PRCM_TVCLK_MGT);
	writel(PRCMU_DPI_CLOCK_SETTING, prcmu_base + PRCM_LCDCLK_MGT);

	/* Release the HW semaphore. */
	writel(0, PRCM_SEM);

	spin_unlock_irqrestore(&clk_mgt_lock, flags);

	return 0;
}