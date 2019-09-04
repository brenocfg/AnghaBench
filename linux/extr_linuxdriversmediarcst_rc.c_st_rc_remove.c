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
struct st_rc_device {int /*<<< orphan*/  rdev; int /*<<< orphan*/  sys_clock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_pm_clear_wake_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 struct st_rc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_rc_remove(struct platform_device *pdev)
{
	struct st_rc_device *rc_dev = platform_get_drvdata(pdev);

	dev_pm_clear_wake_irq(&pdev->dev);
	device_init_wakeup(&pdev->dev, false);
	clk_disable_unprepare(rc_dev->sys_clock);
	rc_unregister_device(rc_dev->rdev);
	return 0;
}