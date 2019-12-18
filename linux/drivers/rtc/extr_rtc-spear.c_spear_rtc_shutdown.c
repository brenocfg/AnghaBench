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
struct spear_rtc_config {int /*<<< orphan*/  clk; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 struct spear_rtc_config* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spear_rtc_disable_interrupt (struct spear_rtc_config*) ; 

__attribute__((used)) static void spear_rtc_shutdown(struct platform_device *pdev)
{
	struct spear_rtc_config *config = platform_get_drvdata(pdev);

	spear_rtc_disable_interrupt(config);
	clk_disable(config->clk);
}