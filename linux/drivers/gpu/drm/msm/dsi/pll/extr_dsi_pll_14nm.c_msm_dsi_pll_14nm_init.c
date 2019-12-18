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
struct msm_dsi_pll {int en_seq_cnt; int /*<<< orphan*/ * enable_seqs; int /*<<< orphan*/  set_usecase; int /*<<< orphan*/  restore_state; int /*<<< orphan*/  save_state; int /*<<< orphan*/  disable_seq; int /*<<< orphan*/  destroy; int /*<<< orphan*/  get_provider; int /*<<< orphan*/  max_rate; int /*<<< orphan*/  min_rate; } ;
struct dsi_pll_14nm {int id; int vco_delay; struct msm_dsi_pll base; int /*<<< orphan*/  postdiv_lock; void* mmio; void* phy_cmn_mmio; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ *,char*,...) ; 
 int ENODEV ; 
 int ENOMEM ; 
 struct msm_dsi_pll* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR_OR_NULL (void*) ; 
 int /*<<< orphan*/  VCO_MAX_RATE ; 
 int /*<<< orphan*/  VCO_MIN_RATE ; 
 struct dsi_pll_14nm* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsi_pll_14nm_destroy ; 
 int /*<<< orphan*/  dsi_pll_14nm_disable_seq ; 
 int /*<<< orphan*/  dsi_pll_14nm_enable_seq ; 
 int /*<<< orphan*/  dsi_pll_14nm_get_provider ; 
 int /*<<< orphan*/  dsi_pll_14nm_restore_state ; 
 int /*<<< orphan*/  dsi_pll_14nm_save_state ; 
 int /*<<< orphan*/  dsi_pll_14nm_set_usecase ; 
 void* msm_ioremap (struct platform_device*,char*,char*) ; 
 struct dsi_pll_14nm** pll_14nm_list ; 
 int pll_14nm_register (struct dsi_pll_14nm*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct msm_dsi_pll *msm_dsi_pll_14nm_init(struct platform_device *pdev, int id)
{
	struct dsi_pll_14nm *pll_14nm;
	struct msm_dsi_pll *pll;
	int ret;

	if (!pdev)
		return ERR_PTR(-ENODEV);

	pll_14nm = devm_kzalloc(&pdev->dev, sizeof(*pll_14nm), GFP_KERNEL);
	if (!pll_14nm)
		return ERR_PTR(-ENOMEM);

	DBG("PLL%d", id);

	pll_14nm->pdev = pdev;
	pll_14nm->id = id;
	pll_14nm_list[id] = pll_14nm;

	pll_14nm->phy_cmn_mmio = msm_ioremap(pdev, "dsi_phy", "DSI_PHY");
	if (IS_ERR_OR_NULL(pll_14nm->phy_cmn_mmio)) {
		DRM_DEV_ERROR(&pdev->dev, "failed to map CMN PHY base\n");
		return ERR_PTR(-ENOMEM);
	}

	pll_14nm->mmio = msm_ioremap(pdev, "dsi_pll", "DSI_PLL");
	if (IS_ERR_OR_NULL(pll_14nm->mmio)) {
		DRM_DEV_ERROR(&pdev->dev, "failed to map PLL base\n");
		return ERR_PTR(-ENOMEM);
	}

	spin_lock_init(&pll_14nm->postdiv_lock);

	pll = &pll_14nm->base;
	pll->min_rate = VCO_MIN_RATE;
	pll->max_rate = VCO_MAX_RATE;
	pll->get_provider = dsi_pll_14nm_get_provider;
	pll->destroy = dsi_pll_14nm_destroy;
	pll->disable_seq = dsi_pll_14nm_disable_seq;
	pll->save_state = dsi_pll_14nm_save_state;
	pll->restore_state = dsi_pll_14nm_restore_state;
	pll->set_usecase = dsi_pll_14nm_set_usecase;

	pll_14nm->vco_delay = 1;

	pll->en_seq_cnt = 1;
	pll->enable_seqs[0] = dsi_pll_14nm_enable_seq;

	ret = pll_14nm_register(pll_14nm);
	if (ret) {
		DRM_DEV_ERROR(&pdev->dev, "failed to register PLL: %d\n", ret);
		return ERR_PTR(ret);
	}

	return pll;
}