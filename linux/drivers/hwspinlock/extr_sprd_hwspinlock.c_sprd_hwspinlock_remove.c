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
struct sprd_hwspinlock_dev {int /*<<< orphan*/  clk; int /*<<< orphan*/  bank; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwspin_lock_unregister (int /*<<< orphan*/ *) ; 
 struct sprd_hwspinlock_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sprd_hwspinlock_remove(struct platform_device *pdev)
{
	struct sprd_hwspinlock_dev *sprd_hwlock = platform_get_drvdata(pdev);

	hwspin_lock_unregister(&sprd_hwlock->bank);
	pm_runtime_disable(&pdev->dev);
	clk_disable_unprepare(sprd_hwlock->clk);
	return 0;
}