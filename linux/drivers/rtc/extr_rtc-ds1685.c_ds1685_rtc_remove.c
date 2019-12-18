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
struct ds1685_priv {int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write ) (struct ds1685_priv*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int RTC_CTRL_4A_RWK_MASK ; 
 int RTC_CTRL_4B_RWK_MASK ; 
 int /*<<< orphan*/  RTC_CTRL_B ; 
 int RTC_CTRL_B_PAU_MASK ; 
 int /*<<< orphan*/  RTC_CTRL_C ; 
 int /*<<< orphan*/  RTC_EXT_CTRL_4A ; 
 int /*<<< orphan*/  RTC_EXT_CTRL_4B ; 
 struct ds1685_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub2 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub3 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub5 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct ds1685_priv*,int /*<<< orphan*/ ,int) ; 
 int stub7 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1685_rtc_remove(struct platform_device *pdev)
{
	struct ds1685_priv *rtc = platform_get_drvdata(pdev);

	/* Read Ctrl B and clear PIE/AIE/UIE. */
	rtc->write(rtc, RTC_CTRL_B,
		   (rtc->read(rtc, RTC_CTRL_B) &
		    ~(RTC_CTRL_B_PAU_MASK)));

	/* Reading Ctrl C auto-clears PF/AF/UF. */
	rtc->read(rtc, RTC_CTRL_C);

	/* Read Ctrl 4B and clear RIE/WIE/KSE. */
	rtc->write(rtc, RTC_EXT_CTRL_4B,
		   (rtc->read(rtc, RTC_EXT_CTRL_4B) &
		    ~(RTC_CTRL_4B_RWK_MASK)));

	/* Manually clear RF/WF/KF in Ctrl 4A. */
	rtc->write(rtc, RTC_EXT_CTRL_4A,
		   (rtc->read(rtc, RTC_EXT_CTRL_4A) &
		    ~(RTC_CTRL_4A_RWK_MASK)));

	return 0;
}