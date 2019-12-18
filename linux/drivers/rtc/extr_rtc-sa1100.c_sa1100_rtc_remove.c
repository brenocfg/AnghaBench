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
struct sa1100_rtc {int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  rtsr; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct sa1100_rtc* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100_rtc_remove(struct platform_device *pdev)
{
	struct sa1100_rtc *info = platform_get_drvdata(pdev);

	if (info) {
		spin_lock_irq(&info->lock);
		writel_relaxed(0, info->rtsr);
		spin_unlock_irq(&info->lock);
		clk_disable_unprepare(info->clk);
	}

	return 0;
}