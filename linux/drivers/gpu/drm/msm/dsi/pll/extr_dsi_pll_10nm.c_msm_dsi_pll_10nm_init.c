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
struct msm_dsi_pll {unsigned long min_rate; unsigned long max_rate; int /*<<< orphan*/  set_usecase; int /*<<< orphan*/  restore_state; int /*<<< orphan*/  save_state; int /*<<< orphan*/  destroy; int /*<<< orphan*/  get_provider; } ;
struct dsi_pll_10nm {int id; int vco_delay; struct msm_dsi_pll base; int /*<<< orphan*/  postdiv_lock; void* mmio; void* phy_cmn_mmio; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int ENOMEM ; 
 struct msm_dsi_pll* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 struct dsi_pll_10nm* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_pll_10nm_destroy ; 
 int /*<<< orphan*/  dsi_pll_10nm_get_provider ; 
 int /*<<< orphan*/  dsi_pll_10nm_restore_state ; 
 int /*<<< orphan*/  dsi_pll_10nm_save_state ; 
 int /*<<< orphan*/  dsi_pll_10nm_set_usecase ; 
 int /*<<< orphan*/  msm_dsi_pll_save_state (struct msm_dsi_pll*) ; 
 void* msm_ioremap (struct platform_device*,char*,char*) ; 
 struct dsi_pll_10nm** pll_10nm_list ; 
 int pll_10nm_register (struct dsi_pll_10nm*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct msm_dsi_pll *msm_dsi_pll_10nm_init(struct platform_device *pdev, int id)
{
	struct dsi_pll_10nm *pll_10nm;
	struct msm_dsi_pll *pll;
	int ret;

	pll_10nm = devm_kzalloc(&pdev->dev, sizeof(*pll_10nm), GFP_KERNEL);
	if (!pll_10nm)
		return ERR_PTR(-ENOMEM);

	DBG("DSI PLL%d", id);

	pll_10nm->pdev = pdev;
	pll_10nm->id = id;
	pll_10nm_list[id] = pll_10nm;

	pll_10nm->phy_cmn_mmio = msm_ioremap(pdev, "dsi_phy", "DSI_PHY");
	if (IS_ERR_OR_NULL(pll_10nm->phy_cmn_mmio)) {
		DRM_DEV_ERROR(&pdev->dev, "failed to map CMN PHY base\n");
		return ERR_PTR(-ENOMEM);
	}

	pll_10nm->mmio = msm_ioremap(pdev, "dsi_pll", "DSI_PLL");
	if (IS_ERR_OR_NULL(pll_10nm->mmio)) {
		DRM_DEV_ERROR(&pdev->dev, "failed to map PLL base\n");
		return ERR_PTR(-ENOMEM);
	}

	spin_lock_init(&pll_10nm->postdiv_lock);

	pll = &pll_10nm->base;
	pll->min_rate = 1000000000UL;
	pll->max_rate = 3500000000UL;
	pll->get_provider = dsi_pll_10nm_get_provider;
	pll->destroy = dsi_pll_10nm_destroy;
	pll->save_state = dsi_pll_10nm_save_state;
	pll->restore_state = dsi_pll_10nm_restore_state;
	pll->set_usecase = dsi_pll_10nm_set_usecase;

	pll_10nm->vco_delay = 1;

	ret = pll_10nm_register(pll_10nm);
	if (ret) {
		DRM_DEV_ERROR(&pdev->dev, "failed to register PLL: %d\n", ret);
		return ERR_PTR(ret);
	}

	/* TODO: Remove this when we have proper display handover support */
	msm_dsi_pll_save_state(pll);

	return pll;
}