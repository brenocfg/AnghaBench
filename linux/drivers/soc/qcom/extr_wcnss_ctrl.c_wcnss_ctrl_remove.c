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
struct wcnss_ctrl {int /*<<< orphan*/  probe_work; } ;
struct rpmsg_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 struct wcnss_ctrl* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void wcnss_ctrl_remove(struct rpmsg_device *rpdev)
{
	struct wcnss_ctrl *wcnss = dev_get_drvdata(&rpdev->dev);

	cancel_work_sync(&wcnss->probe_work);
	of_platform_depopulate(&rpdev->dev);
}