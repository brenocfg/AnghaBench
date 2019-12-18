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
typedef  int /*<<< orphan*/  u8 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_rtc {int /*<<< orphan*/  pctldev; TYPE_1__* type; scalar_t__ has_ext_clk; int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* lock ) (struct omap_rtc*) ;int /*<<< orphan*/  (* unlock ) (struct omap_rtc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OMAP_RTC_INTERRUPTS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_OSC_REG ; 
 int /*<<< orphan*/  OMAP_RTC_OSC_SEL_32KCLK_SRC ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * omap_rtc_power_off ; 
 struct omap_rtc* omap_rtc_power_off_rtc ; 
 int /*<<< orphan*/  pinctrl_unregister (int /*<<< orphan*/ ) ; 
 struct omap_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/ * pm_power_off ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_read (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_write (struct omap_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub2 (struct omap_rtc*) ; 

__attribute__((used)) static int omap_rtc_remove(struct platform_device *pdev)
{
	struct omap_rtc *rtc = platform_get_drvdata(pdev);
	u8 reg;

	if (pm_power_off == omap_rtc_power_off &&
			omap_rtc_power_off_rtc == rtc) {
		pm_power_off = NULL;
		omap_rtc_power_off_rtc = NULL;
	}

	device_init_wakeup(&pdev->dev, 0);

	if (!IS_ERR(rtc->clk))
		clk_disable_unprepare(rtc->clk);

	rtc->type->unlock(rtc);
	/* leave rtc running, but disable irqs */
	rtc_write(rtc, OMAP_RTC_INTERRUPTS_REG, 0);

	if (rtc->has_ext_clk) {
		reg = rtc_read(rtc, OMAP_RTC_OSC_REG);
		reg &= ~OMAP_RTC_OSC_SEL_32KCLK_SRC;
		rtc_write(rtc, OMAP_RTC_OSC_REG, reg);
	}

	rtc->type->lock(rtc);

	/* Disable the clock/module */
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	/* Remove ext_wakeup pinconf */
	pinctrl_unregister(rtc->pctldev);

	return 0;
}