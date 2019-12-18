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
struct rtc_plat_data {int /*<<< orphan*/  clk_ipg; int /*<<< orphan*/  clk_ref; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct rtc_plat_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int mxc_rtc_remove(struct platform_device *pdev)
{
	struct rtc_plat_data *pdata = platform_get_drvdata(pdev);

	clk_disable_unprepare(pdata->clk_ref);
	clk_disable_unprepare(pdata->clk_ipg);

	return 0;
}