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
struct platform_device {int dummy; } ;
struct lpc24xx_rtc {int /*<<< orphan*/  clk_reg; int /*<<< orphan*/  clk_rtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LPC178X_CCALEN ; 
 int /*<<< orphan*/  LPC24XX_ALARM_DISABLE ; 
 int /*<<< orphan*/  LPC24XX_AMR ; 
 int /*<<< orphan*/  LPC24XX_CCR ; 
 int /*<<< orphan*/  LPC24XX_CIIR ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct lpc24xx_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc24xx_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lpc24xx_rtc_remove(struct platform_device *pdev)
{
	struct lpc24xx_rtc *rtc = platform_get_drvdata(pdev);

	/* Ensure all interrupt sources are masked */
	rtc_writel(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);
	rtc_writel(rtc, LPC24XX_CIIR, 0);

	rtc_writel(rtc, LPC24XX_CCR, LPC178X_CCALEN);

	clk_disable_unprepare(rtc->clk_rtc);
	clk_disable_unprepare(rtc->clk_reg);

	return 0;
}