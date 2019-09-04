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
struct bt_bmc {int /*<<< orphan*/  poll_timer; int /*<<< orphan*/  irq; int /*<<< orphan*/  miscdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct bt_bmc* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bt_bmc_remove(struct platform_device *pdev)
{
	struct bt_bmc *bt_bmc = dev_get_drvdata(&pdev->dev);

	misc_deregister(&bt_bmc->miscdev);
	if (!bt_bmc->irq)
		del_timer_sync(&bt_bmc->poll_timer);
	return 0;
}