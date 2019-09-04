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
struct gsc_dev {int num_clocks; int /*<<< orphan*/ * clock; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gsc_unregister_m2m_device (struct gsc_dev*) ; 
 struct gsc_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gsc_remove(struct platform_device *pdev)
{
	struct gsc_dev *gsc = platform_get_drvdata(pdev);
	int i;

	pm_runtime_get_sync(&pdev->dev);

	gsc_unregister_m2m_device(gsc);
	v4l2_device_unregister(&gsc->v4l2_dev);

	vb2_dma_contig_clear_max_seg_size(&pdev->dev);
	for (i = 0; i < gsc->num_clocks; i++)
		clk_disable_unprepare(gsc->clock[i]);

	pm_runtime_put_noidle(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	dev_dbg(&pdev->dev, "%s driver unloaded\n", pdev->name);
	return 0;
}