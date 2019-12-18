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
struct msm_drm_private {int /*<<< orphan*/ * mdss; } ;
struct dss_module_power {int /*<<< orphan*/  clk_config; int /*<<< orphan*/  num_clk; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct dpu_mdss {int num_paths; int /*<<< orphan*/ * mmio; int /*<<< orphan*/ * path; struct dss_module_power mp; } ;

/* Variables and functions */
 int /*<<< orphan*/  _dpu_mdss_irq_domain_fini (struct dpu_mdss*) ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icc_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_dss_put_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_suspend (int /*<<< orphan*/ ) ; 
 struct dpu_mdss* to_dpu_mdss (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dpu_mdss_destroy(struct drm_device *dev)
{
	struct platform_device *pdev = to_platform_device(dev->dev);
	struct msm_drm_private *priv = dev->dev_private;
	struct dpu_mdss *dpu_mdss = to_dpu_mdss(priv->mdss);
	struct dss_module_power *mp = &dpu_mdss->mp;
	int irq;
	int i;

	pm_runtime_suspend(dev->dev);
	pm_runtime_disable(dev->dev);
	_dpu_mdss_irq_domain_fini(dpu_mdss);
	irq = platform_get_irq(pdev, 0);
	irq_set_chained_handler_and_data(irq, NULL, NULL);
	msm_dss_put_clk(mp->clk_config, mp->num_clk);
	devm_kfree(&pdev->dev, mp->clk_config);

	for (i = 0; i < dpu_mdss->num_paths; i++)
		icc_put(dpu_mdss->path[i]);

	if (dpu_mdss->mmio)
		devm_iounmap(&pdev->dev, dpu_mdss->mmio);
	dpu_mdss->mmio = NULL;
	priv->mdss = NULL;
}