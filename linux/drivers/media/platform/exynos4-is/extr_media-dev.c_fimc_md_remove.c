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
struct fimc_md {int /*<<< orphan*/  media_dev; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  subdev_notifier; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_subdev_conf_mode ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fimc_md_pipelines_free (struct fimc_md*) ; 
 int /*<<< orphan*/  fimc_md_put_clocks (struct fimc_md*) ; 
 int /*<<< orphan*/  fimc_md_unregister_clk_provider (struct fimc_md*) ; 
 int /*<<< orphan*/  fimc_md_unregister_entities (struct fimc_md*) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 struct fimc_md* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fimc_md_remove(struct platform_device *pdev)
{
	struct fimc_md *fmd = platform_get_drvdata(pdev);

	if (!fmd)
		return 0;

	fimc_md_unregister_clk_provider(fmd);
	v4l2_async_notifier_unregister(&fmd->subdev_notifier);
	v4l2_async_notifier_cleanup(&fmd->subdev_notifier);

	v4l2_device_unregister(&fmd->v4l2_dev);
	device_remove_file(&pdev->dev, &dev_attr_subdev_conf_mode);
	fimc_md_unregister_entities(fmd);
	fimc_md_pipelines_free(fmd);
	media_device_unregister(&fmd->media_dev);
	media_device_cleanup(&fmd->media_dev);
	fimc_md_put_clocks(fmd);

	return 0;
}