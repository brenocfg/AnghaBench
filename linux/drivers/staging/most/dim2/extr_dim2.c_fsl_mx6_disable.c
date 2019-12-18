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
struct dim2_hdm {scalar_t__ clk_speed; int /*<<< orphan*/  clk; int /*<<< orphan*/  clk_pll; } ;

/* Variables and functions */
 scalar_t__ CLK_2048FS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct dim2_hdm* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static void fsl_mx6_disable(struct platform_device *pdev)
{
	struct dim2_hdm *dev = platform_get_drvdata(pdev);

	if (dev->clk_speed >= CLK_2048FS)
		clk_disable_unprepare(dev->clk_pll);

	clk_disable_unprepare(dev->clk);
}