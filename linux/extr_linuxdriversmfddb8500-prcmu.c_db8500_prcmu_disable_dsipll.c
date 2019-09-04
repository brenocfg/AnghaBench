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
 int /*<<< orphan*/  PRCMU_DISABLE_ESCAPE_CLOCK_DIV ; 
 int /*<<< orphan*/  PRCMU_DISABLE_PLLDSI ; 
 int /*<<< orphan*/  PRCM_DSITVCLK_DIV ; 
 int /*<<< orphan*/  PRCM_PLLDSI_ENABLE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int db8500_prcmu_disable_dsipll(void)
{
	/* Disable dsi pll */
	writel(PRCMU_DISABLE_PLLDSI, PRCM_PLLDSI_ENABLE);
	/* Disable  escapeclock */
	writel(PRCMU_DISABLE_ESCAPE_CLOCK_DIV, PRCM_DSITVCLK_DIV);
	return 0;
}