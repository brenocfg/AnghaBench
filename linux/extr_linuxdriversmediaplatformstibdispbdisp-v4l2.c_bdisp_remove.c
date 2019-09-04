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
struct platform_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; } ;
struct bdisp_dev {int /*<<< orphan*/  clock; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdisp_debugfs_remove (struct bdisp_dev*) ; 
 int /*<<< orphan*/  bdisp_hw_free_filters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bdisp_unregister_device (struct bdisp_dev*) ; 
 int /*<<< orphan*/  clk_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct bdisp_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bdisp_remove(struct platform_device *pdev)
{
	struct bdisp_dev *bdisp = platform_get_drvdata(pdev);

	bdisp_unregister_device(bdisp);

	bdisp_hw_free_filters(bdisp->dev);

	pm_runtime_disable(&pdev->dev);

	bdisp_debugfs_remove(bdisp);

	v4l2_device_unregister(&bdisp->v4l2_dev);

	if (!IS_ERR(bdisp->clock))
		clk_unprepare(bdisp->clock);

	dev_dbg(&pdev->dev, "%s driver unloaded\n", pdev->name);

	return 0;
}