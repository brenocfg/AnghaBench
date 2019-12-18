#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct msm_drm_private {int /*<<< orphan*/ * kms; } ;
struct TYPE_6__ {int /*<<< orphan*/  base; } ;
struct mdp5_kms {int rpm_enabled; int caps; TYPE_3__ base; int /*<<< orphan*/ * ctlm; int /*<<< orphan*/ * cfg; int /*<<< orphan*/ * mmio; int /*<<< orphan*/ * smp; int /*<<< orphan*/  core_clk; int /*<<< orphan*/  lut_clk; int /*<<< orphan*/  vsync_clk; int /*<<< orphan*/  ahb_clk; int /*<<< orphan*/  axi_clk; struct platform_device* pdev; struct drm_device* dev; int /*<<< orphan*/  resource_lock; } ;
struct mdp5_cfg {TYPE_2__* hw; } ;
struct drm_device {struct msm_drm_private* dev_private; } ;
struct TYPE_4__ {int caps; } ;
struct TYPE_5__ {int max_clk; int /*<<< orphan*/  smp; TYPE_1__ mdp; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int MDP_CAP_SMP ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,int) ; 
 struct mdp5_kms* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int get_clk (struct platform_device*,int /*<<< orphan*/ *,char*,int) ; 
 int hwmixer_init (struct mdp5_kms*) ; 
 int hwpipe_init (struct mdp5_kms*) ; 
 int interface_init (struct mdp5_kms*) ; 
 struct mdp5_cfg* mdp5_cfg_get_config (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mdp5_cfg_init (struct mdp5_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mdp5_ctlm_init (struct drm_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdp5_destroy (struct platform_device*) ; 
 int mdp5_global_obj_init (struct mdp5_kms*) ; 
 int /*<<< orphan*/ * mdp5_smp_init (struct mdp5_kms*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * msm_ioremap (struct platform_device*,char*,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct mdp5_kms*) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_mdp_hw_revision (struct mdp5_kms*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mdp5_init(struct platform_device *pdev, struct drm_device *dev)
{
	struct msm_drm_private *priv = dev->dev_private;
	struct mdp5_kms *mdp5_kms;
	struct mdp5_cfg *config;
	u32 major, minor;
	int ret;

	mdp5_kms = devm_kzalloc(&pdev->dev, sizeof(*mdp5_kms), GFP_KERNEL);
	if (!mdp5_kms) {
		ret = -ENOMEM;
		goto fail;
	}

	platform_set_drvdata(pdev, mdp5_kms);

	spin_lock_init(&mdp5_kms->resource_lock);

	mdp5_kms->dev = dev;
	mdp5_kms->pdev = pdev;

	ret = mdp5_global_obj_init(mdp5_kms);
	if (ret)
		goto fail;

	mdp5_kms->mmio = msm_ioremap(pdev, "mdp_phys", "MDP5");
	if (IS_ERR(mdp5_kms->mmio)) {
		ret = PTR_ERR(mdp5_kms->mmio);
		goto fail;
	}

	/* mandatory clocks: */
	ret = get_clk(pdev, &mdp5_kms->axi_clk, "bus", true);
	if (ret)
		goto fail;
	ret = get_clk(pdev, &mdp5_kms->ahb_clk, "iface", true);
	if (ret)
		goto fail;
	ret = get_clk(pdev, &mdp5_kms->core_clk, "core", true);
	if (ret)
		goto fail;
	ret = get_clk(pdev, &mdp5_kms->vsync_clk, "vsync", true);
	if (ret)
		goto fail;

	/* optional clocks: */
	get_clk(pdev, &mdp5_kms->lut_clk, "lut", false);

	/* we need to set a default rate before enabling.  Set a safe
	 * rate first, then figure out hw revision, and then set a
	 * more optimal rate:
	 */
	clk_set_rate(mdp5_kms->core_clk, 200000000);

	pm_runtime_enable(&pdev->dev);
	mdp5_kms->rpm_enabled = true;

	read_mdp_hw_revision(mdp5_kms, &major, &minor);

	mdp5_kms->cfg = mdp5_cfg_init(mdp5_kms, major, minor);
	if (IS_ERR(mdp5_kms->cfg)) {
		ret = PTR_ERR(mdp5_kms->cfg);
		mdp5_kms->cfg = NULL;
		goto fail;
	}

	config = mdp5_cfg_get_config(mdp5_kms->cfg);
	mdp5_kms->caps = config->hw->mdp.caps;

	/* TODO: compute core clock rate at runtime */
	clk_set_rate(mdp5_kms->core_clk, config->hw->max_clk);

	/*
	 * Some chipsets have a Shared Memory Pool (SMP), while others
	 * have dedicated latency buffering per source pipe instead;
	 * this section initializes the SMP:
	 */
	if (mdp5_kms->caps & MDP_CAP_SMP) {
		mdp5_kms->smp = mdp5_smp_init(mdp5_kms, &config->hw->smp);
		if (IS_ERR(mdp5_kms->smp)) {
			ret = PTR_ERR(mdp5_kms->smp);
			mdp5_kms->smp = NULL;
			goto fail;
		}
	}

	mdp5_kms->ctlm = mdp5_ctlm_init(dev, mdp5_kms->mmio, mdp5_kms->cfg);
	if (IS_ERR(mdp5_kms->ctlm)) {
		ret = PTR_ERR(mdp5_kms->ctlm);
		mdp5_kms->ctlm = NULL;
		goto fail;
	}

	ret = hwpipe_init(mdp5_kms);
	if (ret)
		goto fail;

	ret = hwmixer_init(mdp5_kms);
	if (ret)
		goto fail;

	ret = interface_init(mdp5_kms);
	if (ret)
		goto fail;

	/* set uninit-ed kms */
	priv->kms = &mdp5_kms->base.base;

	return 0;
fail:
	mdp5_destroy(pdev);
	return ret;
}