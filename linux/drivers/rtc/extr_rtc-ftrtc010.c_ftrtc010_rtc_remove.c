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
struct ftrtc010_rtc {int /*<<< orphan*/  pclk; int /*<<< orphan*/  extclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct ftrtc010_rtc* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int ftrtc010_rtc_remove(struct platform_device *pdev)
{
	struct ftrtc010_rtc *rtc = platform_get_drvdata(pdev);

	if (!IS_ERR(rtc->extclk))
		clk_disable_unprepare(rtc->extclk);
	if (!IS_ERR(rtc->pclk))
		clk_disable_unprepare(rtc->pclk);

	return 0;
}