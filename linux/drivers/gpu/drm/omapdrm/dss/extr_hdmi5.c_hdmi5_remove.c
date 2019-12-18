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
struct omap_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  component_del (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hdmi5_component_ops ; 
 int /*<<< orphan*/  hdmi5_uninit_output (struct omap_hdmi*) ; 
 int /*<<< orphan*/  kfree (struct omap_hdmi*) ; 
 struct omap_hdmi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hdmi5_remove(struct platform_device *pdev)
{
	struct omap_hdmi *hdmi = platform_get_drvdata(pdev);

	component_del(&pdev->dev, &hdmi5_component_ops);

	hdmi5_uninit_output(hdmi);

	pm_runtime_disable(&pdev->dev);

	kfree(hdmi);
	return 0;
}