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
struct vpfe_device {int /*<<< orphan*/  video_dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  notifier; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct vpfe_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vpfe_dbg (int,struct vpfe_device*,char*) ; 

__attribute__((used)) static int vpfe_remove(struct platform_device *pdev)
{
	struct vpfe_device *vpfe = platform_get_drvdata(pdev);

	vpfe_dbg(2, vpfe, "vpfe_remove\n");

	pm_runtime_disable(&pdev->dev);

	v4l2_async_notifier_unregister(&vpfe->notifier);
	v4l2_async_notifier_cleanup(&vpfe->notifier);
	v4l2_device_unregister(&vpfe->v4l2_dev);
	video_unregister_device(&vpfe->video_dev);

	return 0;
}