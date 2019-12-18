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
struct dss_module_power {scalar_t__ num_clk; int /*<<< orphan*/  clk_config; } ;
struct dpu_kms {scalar_t__ rpm_enabled; struct dss_module_power mp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_dss_put_clk (int /*<<< orphan*/ ,scalar_t__) ; 
 struct dpu_kms* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static void dpu_unbind(struct device *dev, struct device *master, void *data)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct dpu_kms *dpu_kms = platform_get_drvdata(pdev);
	struct dss_module_power *mp = &dpu_kms->mp;

	msm_dss_put_clk(mp->clk_config, mp->num_clk);
	devm_kfree(&pdev->dev, mp->clk_config);
	mp->num_clk = 0;

	if (dpu_kms->rpm_enabled)
		pm_runtime_disable(&pdev->dev);
}