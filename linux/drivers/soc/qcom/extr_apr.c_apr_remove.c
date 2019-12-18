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
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct apr {int /*<<< orphan*/  rxwq; } ;

/* Variables and functions */
 int /*<<< orphan*/  apr_remove_device ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct apr* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_for_each_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apr_remove(struct rpmsg_device *rpdev)
{
	struct apr *apr = dev_get_drvdata(&rpdev->dev);

	device_for_each_child(&rpdev->dev, NULL, apr_remove_device);
	flush_workqueue(apr->rxwq);
	destroy_workqueue(apr->rxwq);
}