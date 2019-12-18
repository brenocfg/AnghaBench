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
struct dpu_mdss {int /*<<< orphan*/ * mmio; TYPE_1__ base; struct dss_module_power mp; int /*<<< orphan*/  mmio_len; } ;

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
 int /*<<< orphan*/  dpu_mdss_icc_request_bw (TYPE_1__*) ; 
 int /*<<< orphan*/  dpu_mdss_irq ; 
 int dpu_mdss_parse_data_bus_icc_path (struct drm_device*,struct dpu_mdss*) ; 
 int /*<<< orphan*/  irq_set_chained_handler_and_data (int,int /*<<< orphan*/ ,struct dpu_mdss*) ; 
 int /*<<< orphan*/  mdss_funcs ; 
 int msm_dss_parse_clock (struct platform_device*,struct dss_module_power*) ; 
 int /*<<< orphan*/  msm_dss_put_clk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * msm_ioremap (struct platform_device*,char*,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
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
	int irq;

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

	ret = dpu_mdss_parse_data_bus_icc_path(dev, dpu_mdss);
	if (ret)
		return ret;

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

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		goto irq_error;

	irq_set_chained_handler_and_data(irq, dpu_mdss_irq,
					 dpu_mdss);

	priv->mdss = &dpu_mdss->base;

	pm_runtime_enable(dev->dev);

	dpu_mdss_icc_request_bw(priv->mdss);

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