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
struct TYPE_6__ {scalar_t__ autoneg; } ;
struct TYPE_4__ {int (* an_config ) (struct xgbe_prv_data*) ;} ;
struct TYPE_5__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {int /*<<< orphan*/  an_mutex; int /*<<< orphan*/  dev_state; int /*<<< orphan*/  an_irq; void* kx_state; void* kr_state; void* an_state; void* an_result; int /*<<< orphan*/  netdev; int /*<<< orphan*/  kr_redrv; TYPE_3__ phy; TYPE_2__ phy_if; int /*<<< orphan*/  link_check; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int EINVAL ; 
 void* XGBE_AN_READY ; 
 int /*<<< orphan*/  XGBE_LINK_ERR ; 
 int /*<<< orphan*/  XGBE_LINK_INIT ; 
 int /*<<< orphan*/  XGBE_MODE_KR ; 
 int /*<<< orphan*/  XGBE_MODE_KX_1000 ; 
 int /*<<< orphan*/  XGBE_MODE_KX_2500 ; 
 int /*<<< orphan*/  XGBE_MODE_SFI ; 
 int /*<<< orphan*/  XGBE_MODE_SGMII_100 ; 
 int /*<<< orphan*/  XGBE_MODE_SGMII_1000 ; 
 int /*<<< orphan*/  XGBE_MODE_X ; 
 void* XGBE_RX_BPA ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_clear_interrupts_all (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_disable_all (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_init (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_an_restart (struct xgbe_prv_data*) ; 
 int xgbe_phy_config_fixed (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_set_mode (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ xgbe_use_mode (struct xgbe_prv_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __xgbe_phy_config_aneg(struct xgbe_prv_data *pdata, bool set_mode)
{
	int ret;

	mutex_lock(&pdata->an_mutex);

	set_bit(XGBE_LINK_INIT, &pdata->dev_state);
	pdata->link_check = jiffies;

	ret = pdata->phy_if.phy_impl.an_config(pdata);
	if (ret)
		goto out;

	if (pdata->phy.autoneg != AUTONEG_ENABLE) {
		ret = xgbe_phy_config_fixed(pdata);
		if (ret || !pdata->kr_redrv)
			goto out;

		netif_dbg(pdata, link, pdata->netdev, "AN redriver support\n");
	} else {
		netif_dbg(pdata, link, pdata->netdev, "AN PHY configuration\n");
	}

	/* Disable auto-negotiation interrupt */
	disable_irq(pdata->an_irq);

	if (set_mode) {
		/* Start auto-negotiation in a supported mode */
		if (xgbe_use_mode(pdata, XGBE_MODE_KR)) {
			xgbe_set_mode(pdata, XGBE_MODE_KR);
		} else if (xgbe_use_mode(pdata, XGBE_MODE_KX_2500)) {
			xgbe_set_mode(pdata, XGBE_MODE_KX_2500);
		} else if (xgbe_use_mode(pdata, XGBE_MODE_KX_1000)) {
			xgbe_set_mode(pdata, XGBE_MODE_KX_1000);
		} else if (xgbe_use_mode(pdata, XGBE_MODE_SFI)) {
			xgbe_set_mode(pdata, XGBE_MODE_SFI);
		} else if (xgbe_use_mode(pdata, XGBE_MODE_X)) {
			xgbe_set_mode(pdata, XGBE_MODE_X);
		} else if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_1000)) {
			xgbe_set_mode(pdata, XGBE_MODE_SGMII_1000);
		} else if (xgbe_use_mode(pdata, XGBE_MODE_SGMII_100)) {
			xgbe_set_mode(pdata, XGBE_MODE_SGMII_100);
		} else {
			enable_irq(pdata->an_irq);
			ret = -EINVAL;
			goto out;
		}
	}

	/* Disable and stop any in progress auto-negotiation */
	xgbe_an_disable_all(pdata);

	/* Clear any auto-negotitation interrupts */
	xgbe_an_clear_interrupts_all(pdata);

	pdata->an_result = XGBE_AN_READY;
	pdata->an_state = XGBE_AN_READY;
	pdata->kr_state = XGBE_RX_BPA;
	pdata->kx_state = XGBE_RX_BPA;

	/* Re-enable auto-negotiation interrupt */
	enable_irq(pdata->an_irq);

	xgbe_an_init(pdata);
	xgbe_an_restart(pdata);

out:
	if (ret)
		set_bit(XGBE_LINK_ERR, &pdata->dev_state);
	else
		clear_bit(XGBE_LINK_ERR, &pdata->dev_state);

	mutex_unlock(&pdata->an_mutex);

	return ret;
}