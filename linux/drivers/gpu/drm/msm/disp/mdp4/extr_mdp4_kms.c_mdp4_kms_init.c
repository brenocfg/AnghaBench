#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_kms {int irq; struct msm_gem_address_space* aspace; } ;
struct msm_gem_address_space {TYPE_3__* mmu; } ;
struct mdp4_platform_config {scalar_t__ iommu; int /*<<< orphan*/  max_clk; } ;
struct TYPE_8__ {struct msm_kms base; } ;
struct mdp4_kms {int rev; int rpm_enabled; int /*<<< orphan*/  blank_cursor_iova; struct msm_gem_address_space* blank_cursor_bo; struct msm_gem_address_space* lut_clk; struct msm_gem_address_space* clk; struct msm_gem_address_space* axi_clk; struct msm_gem_address_space* pclk; struct msm_gem_address_space* vdd; struct msm_gem_address_space* mmio; struct drm_device* dev; TYPE_4__ base; } ;
struct TYPE_6__ {int max_width; int max_height; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {TYPE_2__ mode_config; int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_1__* funcs; } ;
struct TYPE_5__ {int (* attach ) (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DRM_DEV_INFO (int /*<<< orphan*/ ,char*) ; 
 int ENOMEM ; 
 struct msm_kms* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct msm_gem_address_space*) ; 
 int MSM_BO_SCANOUT ; 
 int MSM_BO_WC ; 
 int PTR_ERR (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  REG_MDP4_DSI_ENABLE ; 
 int /*<<< orphan*/  REG_MDP4_DTV_ENABLE ; 
 int /*<<< orphan*/  REG_MDP4_LCDC_ENABLE ; 
 int /*<<< orphan*/  SZ_16K ; 
 int /*<<< orphan*/  clk_set_rate (struct msm_gem_address_space*,int /*<<< orphan*/ ) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct msm_gem_address_space* devm_regulator_get_exclusive (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  iommu_ports ; 
 int /*<<< orphan*/  kms_funcs ; 
 struct mdp4_kms* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mdp4_destroy (struct msm_kms*) ; 
 int /*<<< orphan*/  mdp4_disable (struct mdp4_kms*) ; 
 int /*<<< orphan*/  mdp4_enable (struct mdp4_kms*) ; 
 struct mdp4_platform_config* mdp4_get_config (struct platform_device*) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp_kms_init (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int modeset_init (struct mdp4_kms*) ; 
 struct msm_gem_address_space* msm_gem_address_space_create (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int msm_gem_get_and_pin_iova (struct msm_gem_address_space*,struct msm_gem_address_space*,int /*<<< orphan*/ *) ; 
 struct msm_gem_address_space* msm_gem_new (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 struct msm_gem_address_space* msm_ioremap (struct platform_device*,int /*<<< orphan*/ *,char*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ ) ; 
 int regulator_enable (struct msm_gem_address_space*) ; 
 int stub1 (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

struct msm_kms *mdp4_kms_init(struct drm_device *dev)
{
	struct platform_device *pdev = to_platform_device(dev->dev);
	struct mdp4_platform_config *config = mdp4_get_config(pdev);
	struct mdp4_kms *mdp4_kms;
	struct msm_kms *kms = NULL;
	struct msm_gem_address_space *aspace;
	int irq, ret;

	mdp4_kms = kzalloc(sizeof(*mdp4_kms), GFP_KERNEL);
	if (!mdp4_kms) {
		DRM_DEV_ERROR(dev->dev, "failed to allocate kms\n");
		ret = -ENOMEM;
		goto fail;
	}

	mdp_kms_init(&mdp4_kms->base, &kms_funcs);

	kms = &mdp4_kms->base.base;

	mdp4_kms->dev = dev;

	mdp4_kms->mmio = msm_ioremap(pdev, NULL, "MDP4");
	if (IS_ERR(mdp4_kms->mmio)) {
		ret = PTR_ERR(mdp4_kms->mmio);
		goto fail;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = irq;
		DRM_DEV_ERROR(dev->dev, "failed to get irq: %d\n", ret);
		goto fail;
	}

	kms->irq = irq;

	/* NOTE: driver for this regulator still missing upstream.. use
	 * _get_exclusive() and ignore the error if it does not exist
	 * (and hope that the bootloader left it on for us)
	 */
	mdp4_kms->vdd = devm_regulator_get_exclusive(&pdev->dev, "vdd");
	if (IS_ERR(mdp4_kms->vdd))
		mdp4_kms->vdd = NULL;

	if (mdp4_kms->vdd) {
		ret = regulator_enable(mdp4_kms->vdd);
		if (ret) {
			DRM_DEV_ERROR(dev->dev, "failed to enable regulator vdd: %d\n", ret);
			goto fail;
		}
	}

	mdp4_kms->clk = devm_clk_get(&pdev->dev, "core_clk");
	if (IS_ERR(mdp4_kms->clk)) {
		DRM_DEV_ERROR(dev->dev, "failed to get core_clk\n");
		ret = PTR_ERR(mdp4_kms->clk);
		goto fail;
	}

	mdp4_kms->pclk = devm_clk_get(&pdev->dev, "iface_clk");
	if (IS_ERR(mdp4_kms->pclk))
		mdp4_kms->pclk = NULL;

	if (mdp4_kms->rev >= 2) {
		mdp4_kms->lut_clk = devm_clk_get(&pdev->dev, "lut_clk");
		if (IS_ERR(mdp4_kms->lut_clk)) {
			DRM_DEV_ERROR(dev->dev, "failed to get lut_clk\n");
			ret = PTR_ERR(mdp4_kms->lut_clk);
			goto fail;
		}
	}

	mdp4_kms->axi_clk = devm_clk_get(&pdev->dev, "bus_clk");
	if (IS_ERR(mdp4_kms->axi_clk)) {
		DRM_DEV_ERROR(dev->dev, "failed to get axi_clk\n");
		ret = PTR_ERR(mdp4_kms->axi_clk);
		goto fail;
	}

	clk_set_rate(mdp4_kms->clk, config->max_clk);
	if (mdp4_kms->lut_clk)
		clk_set_rate(mdp4_kms->lut_clk, config->max_clk);

	pm_runtime_enable(dev->dev);
	mdp4_kms->rpm_enabled = true;

	/* make sure things are off before attaching iommu (bootloader could
	 * have left things on, in which case we'll start getting faults if
	 * we don't disable):
	 */
	mdp4_enable(mdp4_kms);
	mdp4_write(mdp4_kms, REG_MDP4_DTV_ENABLE, 0);
	mdp4_write(mdp4_kms, REG_MDP4_LCDC_ENABLE, 0);
	mdp4_write(mdp4_kms, REG_MDP4_DSI_ENABLE, 0);
	mdp4_disable(mdp4_kms);
	mdelay(16);

	if (config->iommu) {
		aspace = msm_gem_address_space_create(&pdev->dev,
				config->iommu, "mdp4");
		if (IS_ERR(aspace)) {
			ret = PTR_ERR(aspace);
			goto fail;
		}

		kms->aspace = aspace;

		ret = aspace->mmu->funcs->attach(aspace->mmu, iommu_ports,
				ARRAY_SIZE(iommu_ports));
		if (ret)
			goto fail;
	} else {
		DRM_DEV_INFO(dev->dev, "no iommu, fallback to phys "
				"contig buffers for scanout\n");
		aspace = NULL;
	}

	ret = modeset_init(mdp4_kms);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "modeset_init failed: %d\n", ret);
		goto fail;
	}

	mdp4_kms->blank_cursor_bo = msm_gem_new(dev, SZ_16K, MSM_BO_WC | MSM_BO_SCANOUT);
	if (IS_ERR(mdp4_kms->blank_cursor_bo)) {
		ret = PTR_ERR(mdp4_kms->blank_cursor_bo);
		DRM_DEV_ERROR(dev->dev, "could not allocate blank-cursor bo: %d\n", ret);
		mdp4_kms->blank_cursor_bo = NULL;
		goto fail;
	}

	ret = msm_gem_get_and_pin_iova(mdp4_kms->blank_cursor_bo, kms->aspace,
			&mdp4_kms->blank_cursor_iova);
	if (ret) {
		DRM_DEV_ERROR(dev->dev, "could not pin blank-cursor bo: %d\n", ret);
		goto fail;
	}

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;

	return kms;

fail:
	if (kms)
		mdp4_destroy(kms);
	return ERR_PTR(ret);
}