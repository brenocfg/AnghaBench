#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* kr_training_post ) (struct xgbe_prv_data*) ;int /*<<< orphan*/  (* kr_training_pre ) (struct xgbe_prv_data*) ;} ;
struct TYPE_4__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {unsigned int fec_ability; TYPE_2__ phy_if; int /*<<< orphan*/  netdev; } ;
typedef  enum xgbe_rx { ____Placeholder_xgbe_rx } xgbe_rx ;
typedef  enum xgbe_an { ____Placeholder_xgbe_an } xgbe_an ;

/* Variables and functions */
 scalar_t__ MDIO_AN_ADVERTISE ; 
 scalar_t__ MDIO_AN_LPA ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 unsigned int MDIO_PMA_10GBR_FECABLE_ABLE ; 
 unsigned int MDIO_PMA_10GBR_FECABLE_ERRABLE ; 
 scalar_t__ MDIO_PMA_10GBR_FECCTRL ; 
 scalar_t__ MDIO_PMA_10GBR_PMD_CTRL ; 
 int XGBE_AN_PAGE_RECEIVED ; 
 unsigned int XGBE_KR_TRAINING_ENABLE ; 
 unsigned int XGBE_KR_TRAINING_START ; 
 int XGBE_RX_COMPLETE ; 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  stub2 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_in_kr_mode (struct xgbe_prv_data*) ; 

__attribute__((used)) static enum xgbe_an xgbe_an73_tx_training(struct xgbe_prv_data *pdata,
					  enum xgbe_rx *state)
{
	unsigned int ad_reg, lp_reg, reg;

	*state = XGBE_RX_COMPLETE;

	/* If we're not in KR mode then we're done */
	if (!xgbe_in_kr_mode(pdata))
		return XGBE_AN_PAGE_RECEIVED;

	/* Enable/Disable FEC */
	ad_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_ADVERTISE + 2);
	lp_reg = XMDIO_READ(pdata, MDIO_MMD_AN, MDIO_AN_LPA + 2);

	reg = XMDIO_READ(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL);
	reg &= ~(MDIO_PMA_10GBR_FECABLE_ABLE | MDIO_PMA_10GBR_FECABLE_ERRABLE);
	if ((ad_reg & 0xc000) && (lp_reg & 0xc000))
		reg |= pdata->fec_ability;

	XMDIO_WRITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_FECCTRL, reg);

	/* Start KR training */
	if (pdata->phy_if.phy_impl.kr_training_pre)
		pdata->phy_if.phy_impl.kr_training_pre(pdata);

	reg = XMDIO_READ(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL);
	reg |= XGBE_KR_TRAINING_ENABLE;
	reg |= XGBE_KR_TRAINING_START;
	XMDIO_WRITE(pdata, MDIO_MMD_PMAPMD, MDIO_PMA_10GBR_PMD_CTRL, reg);

	netif_dbg(pdata, link, pdata->netdev,
		  "KR training initiated\n");

	if (pdata->phy_if.phy_impl.kr_training_post)
		pdata->phy_if.phy_impl.kr_training_post(pdata);

	return XGBE_AN_PAGE_RECEIVED;
}