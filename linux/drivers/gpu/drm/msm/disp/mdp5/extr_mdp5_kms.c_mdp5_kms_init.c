#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct device {struct device* parent; int /*<<< orphan*/  iommu_fwspec; int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct msm_kms {int irq; struct msm_gem_address_space* aspace; } ;
struct msm_gem_address_space {TYPE_7__* mmu; } ;
struct msm_drm_private {struct msm_kms* kms; } ;
struct mdp5_kms {int /*<<< orphan*/  cfg; struct platform_device* pdev; int /*<<< orphan*/  base; } ;
struct TYPE_10__ {scalar_t__ iommu; } ;
struct mdp5_cfg {TYPE_3__ platform; TYPE_2__* hw; } ;
struct TYPE_12__ {int max_width; int max_height; scalar_t__ min_height; scalar_t__ min_width; } ;
struct drm_device {int vblank_disable_immediate; scalar_t__ max_vblank_count; TYPE_6__* driver; TYPE_5__ mode_config; struct msm_drm_private* dev_private; } ;
struct TYPE_14__ {TYPE_4__* funcs; } ;
struct TYPE_13__ {int /*<<< orphan*/  get_vblank_counter; int /*<<< orphan*/  get_scanout_position; int /*<<< orphan*/  get_vblank_timestamp; } ;
struct TYPE_11__ {int (* attach ) (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/ * base; int /*<<< orphan*/ * connect; } ;
struct TYPE_9__ {TYPE_1__ intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (struct device*,char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_INFO (struct device*,char*) ; 
 struct msm_kms* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct msm_gem_address_space*) ; 
 int MDP5_INTF_NUM_MAX ; 
 int PTR_ERR (struct msm_gem_address_space*) ; 
 int /*<<< orphan*/  REG_MDP5_INTF_FRAME_LINE_COUNT_EN (int) ; 
 int /*<<< orphan*/  REG_MDP5_INTF_TIMING_ENGINE_EN (int) ; 
 int /*<<< orphan*/  drm_calc_vbltimestamp_from_scanoutpos ; 
 int /*<<< orphan*/  iommu_ports ; 
 int irq_of_parse_and_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kms_funcs ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct mdp5_cfg* mdp5_cfg_get_config (int /*<<< orphan*/ ) ; 
 scalar_t__ mdp5_cfg_intf_is_virtual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_get_scanoutpos ; 
 int /*<<< orphan*/  mdp5_get_vblank_counter ; 
 int /*<<< orphan*/  mdp5_kms_destroy (struct msm_kms*) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp_kms_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int modeset_init (struct mdp5_kms*) ; 
 struct msm_gem_address_space* msm_gem_address_space_create (struct device*,scalar_t__,char*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int stub1 (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mdp5_kms* to_mdp5_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (struct msm_kms*) ; 

struct msm_kms *mdp5_kms_init(struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct platform_device *pdev;
	struct mdp5_kms *mdp5_kms;
	struct mdp5_cfg *config;
	struct msm_kms *kms;
	struct msm_gem_address_space *aspace;
	int irq, i, ret;
	struct device *iommu_dev;

	/* priv->kms would have been populated by the MDP5 driver */
	kms = priv->kms;
	if (!kms)
		return NULL;

	mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));

	mdp_kms_init(&mdp5_kms->base, &kms_funcs);

	pdev = mdp5_kms->pdev;

	irq = irq_of_parse_and_map(pdev->dev.of_node, 0);
	if (irq < 0) {
		ret = irq;
		DRM_DEV_ERROR(&pdev->dev, "failed to get irq: %d\n", ret);
		goto fail;
	}

	kms->irq = irq;

	config = mdp5_cfg_get_config(mdp5_kms->cfg);

	/* make sure things are off before attaching iommu (bootloader could
	 * have left things on, in which case we'll start getting faults if
	 * we don't disable):
	 */
	pm_runtime_get_sync(&pdev->dev);
	for (i = 0; i < MDP5_INTF_NUM_MAX; i++) {
		if (mdp5_cfg_intf_is_virtual(config->hw->intf.connect[i]) ||
		    !config->hw->intf.base[i])
			continue;
		mdp5_write(mdp5_kms, REG_MDP5_INTF_TIMING_ENGINE_EN(i), 0);

		mdp5_write(mdp5_kms, REG_MDP5_INTF_FRAME_LINE_COUNT_EN(i), 0x3);
	}
	mdelay(16);

	if (config->platform.iommu) {
		iommu_dev = &pdev->dev;
		if (!iommu_dev->iommu_fwspec)
			iommu_dev = iommu_dev->parent;

		aspace = msm_gem_address_space_create(iommu_dev,
				config->platform.iommu, "mdp5");
		if (IS_ERR(aspace)) {
			ret = PTR_ERR(aspace);
			goto fail;
		}

		kms->aspace = aspace;

		ret = aspace->mmu->funcs->attach(aspace->mmu, iommu_ports,
				ARRAY_SIZE(iommu_ports));
		if (ret) {
			DRM_DEV_ERROR(&pdev->dev, "failed to attach iommu: %d\n",
				ret);
			goto fail;
		}
	} else {
		DRM_DEV_INFO(&pdev->dev,
			 "no iommu, fallback to phys contig buffers for scanout\n");
		aspace = NULL;
	}

	pm_runtime_put_sync(&pdev->dev);

	ret = modeset_init(mdp5_kms);
	if (ret) {
		DRM_DEV_ERROR(&pdev->dev, "modeset_init failed: %d\n", ret);
		goto fail;
	}

	dev->mode_config.min_width = 0;
	dev->mode_config.min_height = 0;
	dev->mode_config.max_width = 0xffff;
	dev->mode_config.max_height = 0xffff;

	dev->driver->get_vblank_timestamp = drm_calc_vbltimestamp_from_scanoutpos;
	dev->driver->get_scanout_position = mdp5_get_scanoutpos;
	dev->driver->get_vblank_counter = mdp5_get_vblank_counter;
	dev->max_vblank_count = 0; /* max_vblank_count is set on each CRTC */
	dev->vblank_disable_immediate = true;

	return kms;
fail:
	if (kms)
		mdp5_kms_destroy(kms);
	return ERR_PTR(ret);
}