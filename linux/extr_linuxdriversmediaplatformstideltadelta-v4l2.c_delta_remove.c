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
struct delta_dev {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  dev; int /*<<< orphan*/  work_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  delta_ipc_exit (struct delta_dev*) ; 
 int /*<<< orphan*/  delta_unregister_device (struct delta_dev*) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 struct delta_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int delta_remove(struct platform_device *pdev)
{
	struct delta_dev *delta = platform_get_drvdata(pdev);

	delta_ipc_exit(delta);

	delta_unregister_device(delta);

	destroy_workqueue(delta->work_queue);

	pm_runtime_put_autosuspend(delta->dev);
	pm_runtime_disable(delta->dev);

	v4l2_device_unregister(&delta->v4l2_dev);

	return 0;
}