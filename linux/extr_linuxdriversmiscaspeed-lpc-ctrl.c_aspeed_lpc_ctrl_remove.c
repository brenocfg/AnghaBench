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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct aspeed_lpc_ctrl {int /*<<< orphan*/  clk; int /*<<< orphan*/  miscdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct aspeed_lpc_ctrl* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aspeed_lpc_ctrl_remove(struct platform_device *pdev)
{
	struct aspeed_lpc_ctrl *lpc_ctrl = dev_get_drvdata(&pdev->dev);

	misc_deregister(&lpc_ctrl->miscdev);
	clk_disable_unprepare(lpc_ctrl->clk);

	return 0;
}