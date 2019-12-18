#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * v4l2_dev; } ;
struct rvin_dev {int /*<<< orphan*/  ctrl_handler; TYPE_2__* group; int /*<<< orphan*/  v4l2_dev; TYPE_1__* info; TYPE_3__ notifier; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_3__ notifier; } ;
struct TYPE_5__ {scalar_t__ use_mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct rvin_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rvin_dma_unregister (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_group_put (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_v4l2_unregister (struct rvin_dev*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (TYPE_3__*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rcar_vin_remove(struct platform_device *pdev)
{
	struct rvin_dev *vin = platform_get_drvdata(pdev);

	pm_runtime_disable(&pdev->dev);

	rvin_v4l2_unregister(vin);

	v4l2_async_notifier_unregister(&vin->notifier);
	v4l2_async_notifier_cleanup(&vin->notifier);

	if (vin->info->use_mc) {
		mutex_lock(&vin->group->lock);
		if (&vin->v4l2_dev == vin->group->notifier.v4l2_dev) {
			v4l2_async_notifier_unregister(&vin->group->notifier);
			v4l2_async_notifier_cleanup(&vin->group->notifier);
		}
		mutex_unlock(&vin->group->lock);
		rvin_group_put(vin);
	}

	v4l2_ctrl_handler_free(&vin->ctrl_handler);

	rvin_dma_unregister(vin);

	return 0;
}