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
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_drm_private {TYPE_1__* mdss; } ;
struct dss_module_power {int /*<<< orphan*/  clk_config; int /*<<< orphan*/  num_clk; } ;
struct drm_device {int /*<<< orphan*/  dev; struct msm_drm_private* dev_private; } ;
struct TYPE_2__ {int /*<<< orphan*/ * funcs; struct drm_device* dev; } ;
struct dpu_mdss {int /*<<< orphan*/ * mmio; TYPE_1__ base; int /*<<< orphan*/  hwversion; struct dss_module_power mp; int /*<<< orphan*/  mmio_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPU_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int _dpu_mdss_irq_domain_add (struct dpu_mdss*) ; 
 int /*<<< orphan*/  _dpu_mdss_irq_domain_fini (struct dpu_mdss*) ; 
 int /*<<< orphan*/  devm_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dpu_mdss* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct dpu_mdss*) ; 
 int /*<<< orphan*/  dpu_mdss_irq ; 
 int /*<<< orphan*/  mdss_funcs ; 
 int msm_dss_parse_clock (struct platform_device*,struct dss_module_power*) ; 
 int /*<<< orphan*/  msm_dss_put_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msm_ioremap (struct platform_device*,char*,char*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

int dpu_mdss_init(struct drm_device *dev)
{
	struct platform_device *pdev = to_platform_device(dev->dev);
	struct msm_drm_private *priv = dev->dev_private;
	struct resource *res;
	struct dpu_mdss *dpu_mdss;
	struct dss_module_power *mp;
	int ret = 0;

	dpu_mdss = devm_kzalloc(dev->dev, sizeof(*dpu_mdss), GFP_KERNEL);
	if (!dpu_mdss)
		return -ENOMEM;

	dpu_mdss->mmio = msm_ioremap(pdev, "mdss", "mdss");
	if (IS_ERR(dpu_mdss->mmio))
		return PTR_ERR(dpu_mdss->mmio);

	DRM_DEBUG("mapped mdss address space @%pK\n", dpu_mdss->mmio);

	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "mdss");
	if (!res) {
		DRM_ERROR("failed to get memory resource for mdss\n");
		return -ENOMEM;
	}
	dpu_mdss->mmio_len = resource_size(res);

	mp = &dpu_mdss->mp;
	ret = msm_dss_parse_clock(pdev, mp);
	if (ret) {
		DPU_ERROR("failed to parse clocks, ret=%d\n", ret);
		goto clk_parse_err;
	}

	dpu_mdss->base.dev = dev;
	dpu_mdss->base.funcs = &mdss_funcs;

	ret = _dpu_mdss_irq_domain_add(dpu_mdss);
	if (ret)
		goto irq_domain_error;

	ret = devm_request_irq(dev->dev, platform_get_irq(pdev, 0),
			dpu_mdss_irq, 0, "dpu_mdss_isr", dpu_mdss);
	if (ret) {
		DPU_ERROR("failed to init irq: %d\n", ret);
		goto irq_error;
	}

	pm_runtime_enable(dev->dev);

	pm_runtime_get_sync(dev->dev);
	dpu_mdss->hwversion = readl_relaxed(dpu_mdss->mmio);
	pm_runtime_put_sync(dev->dev);

	priv->mdss = &dpu_mdss->base;

	return ret;

irq_error:
	_dpu_mdss_irq_domain_fini(dpu_mdss);
irq_domain_error:
	msm_dss_put_clk(mp->clk_config, mp->num_clk);
clk_parse_err:
	devm_kfree(&pdev->dev, mp->clk_config);
	if (dpu_mdss->mmio)
		devm_iounmap(&pdev->dev, dpu_mdss->mmio);
	dpu_mdss->mmio = NULL;
	return ret;
}