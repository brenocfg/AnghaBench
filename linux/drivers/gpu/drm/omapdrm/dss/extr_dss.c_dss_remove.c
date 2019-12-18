#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dss; int /*<<< orphan*/  clk; } ;
struct dss_device {scalar_t__ video2_pll; scalar_t__ video1_pll; TYPE_1__ debugfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_master_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dss_component_ops ; 
 int /*<<< orphan*/  dss_debugfs_remove_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dss_put_clocks (struct dss_device*) ; 
 int /*<<< orphan*/  dss_uninit_ports (struct dss_device*) ; 
 int /*<<< orphan*/  dss_uninitialize_debugfs (struct dss_device*) ; 
 int /*<<< orphan*/  dss_video_pll_uninit (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dss_device*) ; 
 int /*<<< orphan*/  of_platform_depopulate (int /*<<< orphan*/ *) ; 
 struct dss_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dss_remove(struct platform_device *pdev)
{
	struct dss_device *dss = platform_get_drvdata(pdev);

	of_platform_depopulate(&pdev->dev);

	component_master_del(&pdev->dev, &dss_component_ops);

	dss_debugfs_remove_file(dss->debugfs.clk);
	dss_debugfs_remove_file(dss->debugfs.dss);
	dss_uninitialize_debugfs(dss);

	pm_runtime_disable(&pdev->dev);

	dss_uninit_ports(dss);

	if (dss->video1_pll)
		dss_video_pll_uninit(dss->video1_pll);

	if (dss->video2_pll)
		dss_video_pll_uninit(dss->video2_pll);

	dss_put_clocks(dss);

	kfree(dss);

	return 0;
}