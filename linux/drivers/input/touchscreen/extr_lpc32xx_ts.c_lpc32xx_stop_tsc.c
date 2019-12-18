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
struct lpc32xx_tsc {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int LPC32XX_TSC_ADCCON_AUTO_EN ; 
 int /*<<< orphan*/  LPC32XX_TSC_CON ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int tsc_readl (struct lpc32xx_tsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc_writel (struct lpc32xx_tsc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void lpc32xx_stop_tsc(struct lpc32xx_tsc *tsc)
{
	/* Disable auto mode */
	tsc_writel(tsc, LPC32XX_TSC_CON,
		   tsc_readl(tsc, LPC32XX_TSC_CON) &
			     ~LPC32XX_TSC_ADCCON_AUTO_EN);

	clk_disable_unprepare(tsc->clk);
}