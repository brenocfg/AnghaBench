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
struct sunxi_rsb {int /*<<< orphan*/  clk; int /*<<< orphan*/  rstc; int /*<<< orphan*/  dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct sunxi_rsb* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunxi_rsb_remove_devices ; 

__attribute__((used)) static int sunxi_rsb_remove(struct platform_device *pdev)
{
	struct sunxi_rsb *rsb = platform_get_drvdata(pdev);

	device_for_each_child(rsb->dev, NULL, sunxi_rsb_remove_devices);
	reset_control_assert(rsb->rstc);
	clk_disable_unprepare(rsb->clk);

	return 0;
}