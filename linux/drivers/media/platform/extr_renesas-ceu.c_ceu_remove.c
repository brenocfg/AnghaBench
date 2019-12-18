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
struct ceu_device {int /*<<< orphan*/  vdev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct ceu_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceu_remove(struct platform_device *pdev)
{
	struct ceu_device *ceudev = platform_get_drvdata(pdev);

	pm_runtime_disable(ceudev->dev);

	v4l2_async_notifier_unregister(&ceudev->notifier);

	v4l2_async_notifier_cleanup(&ceudev->notifier);

	v4l2_device_unregister(&ceudev->v4l2_dev);

	video_unregister_device(&ceudev->vdev);

	return 0;
}