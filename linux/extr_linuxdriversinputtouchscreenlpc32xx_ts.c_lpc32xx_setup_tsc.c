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
struct lpc32xx_tsc {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int LPC32XX_TSC_ADCCON_AUTO_EN ; 
 int LPC32XX_TSC_ADCCON_IRQ_TO_FIFO_4 ; 
 int LPC32XX_TSC_ADCCON_POWER_UP ; 
 int LPC32XX_TSC_ADCCON_X_SAMPLE_SIZE (int) ; 
 int LPC32XX_TSC_ADCCON_Y_SAMPLE_SIZE (int) ; 
 int /*<<< orphan*/  LPC32XX_TSC_AUX_MAX ; 
 int /*<<< orphan*/  LPC32XX_TSC_AUX_MIN ; 
 int /*<<< orphan*/  LPC32XX_TSC_AUX_UTR ; 
 int /*<<< orphan*/  LPC32XX_TSC_CON ; 
 int /*<<< orphan*/  LPC32XX_TSC_DTR ; 
 int /*<<< orphan*/  LPC32XX_TSC_DXP ; 
 int /*<<< orphan*/  LPC32XX_TSC_MAX_X ; 
 int LPC32XX_TSC_MAX_XY_VAL ; 
 int /*<<< orphan*/  LPC32XX_TSC_MAX_Y ; 
 int /*<<< orphan*/  LPC32XX_TSC_MIN_X ; 
 int LPC32XX_TSC_MIN_XY_VAL ; 
 int /*<<< orphan*/  LPC32XX_TSC_MIN_Y ; 
 int /*<<< orphan*/  LPC32XX_TSC_RTR ; 
 int /*<<< orphan*/  LPC32XX_TSC_SEL ; 
 int LPC32XX_TSC_SEL_DEFVAL ; 
 int /*<<< orphan*/  LPC32XX_TSC_TTR ; 
 int /*<<< orphan*/  LPC32XX_TSC_UTR ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpc32xx_fifo_clear (struct lpc32xx_tsc*) ; 
 int tsc_readl (struct lpc32xx_tsc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc_writel (struct lpc32xx_tsc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lpc32xx_setup_tsc(struct lpc32xx_tsc *tsc)
{
	u32 tmp;
	int err;

	err = clk_prepare_enable(tsc->clk);
	if (err)
		return err;

	tmp = tsc_readl(tsc, LPC32XX_TSC_CON) & ~LPC32XX_TSC_ADCCON_POWER_UP;

	/* Set the TSC FIFO depth to 4 samples @ 10-bits per sample (max) */
	tmp = LPC32XX_TSC_ADCCON_IRQ_TO_FIFO_4 |
	      LPC32XX_TSC_ADCCON_X_SAMPLE_SIZE(10) |
	      LPC32XX_TSC_ADCCON_Y_SAMPLE_SIZE(10);
	tsc_writel(tsc, LPC32XX_TSC_CON, tmp);

	/* These values are all preset */
	tsc_writel(tsc, LPC32XX_TSC_SEL, LPC32XX_TSC_SEL_DEFVAL);
	tsc_writel(tsc, LPC32XX_TSC_MIN_X, LPC32XX_TSC_MIN_XY_VAL);
	tsc_writel(tsc, LPC32XX_TSC_MAX_X, LPC32XX_TSC_MAX_XY_VAL);
	tsc_writel(tsc, LPC32XX_TSC_MIN_Y, LPC32XX_TSC_MIN_XY_VAL);
	tsc_writel(tsc, LPC32XX_TSC_MAX_Y, LPC32XX_TSC_MAX_XY_VAL);

	/* Aux support is not used */
	tsc_writel(tsc, LPC32XX_TSC_AUX_UTR, 0);
	tsc_writel(tsc, LPC32XX_TSC_AUX_MIN, 0);
	tsc_writel(tsc, LPC32XX_TSC_AUX_MAX, 0);

	/*
	 * Set sample rate to about 240Hz per X/Y pair. A single measurement
	 * consists of 4 pairs which gives about a 60Hz sample rate based on
	 * a stable 32768Hz clock source. Values are in clocks.
	 * Rate is (32768 / (RTR + XCONV + RTR + YCONV + DXP + TTR + UTR) / 4
	 */
	tsc_writel(tsc, LPC32XX_TSC_RTR, 0x2);
	tsc_writel(tsc, LPC32XX_TSC_DTR, 0x2);
	tsc_writel(tsc, LPC32XX_TSC_TTR, 0x10);
	tsc_writel(tsc, LPC32XX_TSC_DXP, 0x4);
	tsc_writel(tsc, LPC32XX_TSC_UTR, 88);

	lpc32xx_fifo_clear(tsc);

	/* Enable automatic ts event capture */
	tsc_writel(tsc, LPC32XX_TSC_CON, tmp | LPC32XX_TSC_ADCCON_AUTO_EN);

	return 0;
}