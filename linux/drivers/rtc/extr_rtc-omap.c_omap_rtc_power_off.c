#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct rtc_device {TYPE_1__ dev; } ;
struct TYPE_10__ {TYPE_2__* type; struct rtc_device* rtc; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* lock ) (TYPE_3__*) ;int /*<<< orphan*/  (* unlock ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int OMAP_RTC_PMIC_EXT_WKUP_EN (int /*<<< orphan*/ ) ; 
 int OMAP_RTC_PMIC_EXT_WKUP_POL (int /*<<< orphan*/ ) ; 
 int OMAP_RTC_PMIC_POWER_EN_EN ; 
 int /*<<< orphan*/  OMAP_RTC_PMIC_REG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  omap_rtc_power_off_program (int /*<<< orphan*/ ) ; 
 TYPE_3__* omap_rtc_power_off_rtc ; 
 int rtc_readl (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static void omap_rtc_power_off(void)
{
	struct rtc_device *rtc = omap_rtc_power_off_rtc->rtc;
	u32 val;

	omap_rtc_power_off_program(rtc->dev.parent);

	/* Set PMIC power enable and EXT_WAKEUP in case PB power on is used */
	omap_rtc_power_off_rtc->type->unlock(omap_rtc_power_off_rtc);
	val = rtc_readl(omap_rtc_power_off_rtc, OMAP_RTC_PMIC_REG);
	val |= OMAP_RTC_PMIC_POWER_EN_EN | OMAP_RTC_PMIC_EXT_WKUP_POL(0) |
			OMAP_RTC_PMIC_EXT_WKUP_EN(0);
	rtc_writel(omap_rtc_power_off_rtc, OMAP_RTC_PMIC_REG, val);
	omap_rtc_power_off_rtc->type->lock(omap_rtc_power_off_rtc);

	/*
	 * Wait for alarm to trigger (within one second) and external PMIC to
	 * power off the system. Add a 500 ms margin for external latencies
	 * (e.g. debounce circuits).
	 */
	mdelay(1500);
}