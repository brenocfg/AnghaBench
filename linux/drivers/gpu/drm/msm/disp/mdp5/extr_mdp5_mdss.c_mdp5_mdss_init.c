#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int dummy; } ;
struct msm_drm_private {TYPE_1__* mdss; } ;
struct TYPE_8__ {int /*<<< orphan*/ * funcs; struct drm_device* dev; } ;
struct mdp5_mdss {void* vdd; TYPE_1__ base; void* vbif; void* mmio; } ;
struct drm_device {TYPE_2__* dev; struct msm_drm_private* dev_private; } ;
struct TYPE_9__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (TYPE_2__*,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 struct mdp5_mdss* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 void* devm_regulator_get (TYPE_2__*,char*) ; 
 int devm_request_irq (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct mdp5_mdss*) ; 
 int /*<<< orphan*/  mdss_funcs ; 
 int /*<<< orphan*/  mdss_irq ; 
 int mdss_irq_domain_init (struct mdp5_mdss*) ; 
 void* msm_ioremap (struct platform_device*,char*,char*) ; 
 int msm_mdss_get_clocks (struct mdp5_mdss*) ; 
 int /*<<< orphan*/  of_device_is_compatible (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  regulator_disable (void*) ; 
 int regulator_enable (void*) ; 
 struct platform_device* to_platform_device (TYPE_2__*) ; 

int mdp5_mdss_init(struct drm_device *dev)
{
	struct platform_device *pdev = to_platform_device(dev->dev);
	struct msm_drm_private *priv = dev->dev_private;
	struct mdp5_mdss *mdp5_mdss;
	int ret;

	DBG("");

	if (!of_device_is_compatible(dev->dev->of_node, "qcom,mdss"))
		return 0;

	mdp5_mdss = devm_kzalloc(dev->dev, sizeof(*mdp5_mdss), GFP_KERNEL);
	if (!mdp5_mdss) {
		ret = -ENOMEM;
		goto fail;
	}

	mdp5_mdss->base.dev = dev;

	mdp5_mdss->mmio = msm_ioremap(pdev, "mdss_phys", "MDSS");
	if (IS_ERR(mdp5_mdss->mmio)) {
		ret = PTR_ERR(mdp5_mdss->mmio);
		goto fail;
	}

	mdp5_mdss->vbif = msm_ioremap(pdev, "vbif_phys", "VBIF");
	if (IS_ERR(mdp5_mdss->vbif)) {
		ret = PTR_ERR(mdp5_mdss->vbif);
		goto fail;
	}

	ret = msm_mdss_get_clocks(mdp5_mdss);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "failed to get clocks: %d\n", ret);
		goto fail;
	}

	/* Regulator to enable GDSCs in downstream kernels */
	mdp5_mdss->vdd = devm_regulator_get(dev->dev, "vdd");
	if (IS_ERR(mdp5_mdss->vdd)) {
		ret = PTR_ERR(mdp5_mdss->vdd);
		goto fail;
	}

	ret = regulator_enable(mdp5_mdss->vdd);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "failed to enable regulator vdd: %d\n",
			ret);
		goto fail;
	}

	ret = devm_request_irq(dev->dev, platform_get_irq(pdev, 0),
			       mdss_irq, 0, "mdss_isr", mdp5_mdss);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "failed to init irq: %d\n", ret);
		goto fail_irq;
	}

	ret = mdss_irq_domain_init(mdp5_mdss);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "failed to init sub-block irqs: %d\n", ret);
		goto fail_irq;
	}

	mdp5_mdss->base.funcs = &mdss_funcs;
	priv->mdss = &mdp5_mdss->base;

	pm_runtime_enable(dev->dev);

	return 0;
fail_irq:
	regulator_disable(mdp5_mdss->vdd);
fail:
	return ret;
}