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
struct ethtool_link_ksettings {int dummy; } ;
struct TYPE_6__ {scalar_t__ rx_pause; scalar_t__ tx_pause; int /*<<< orphan*/  pause_autoneg; scalar_t__ link; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; int /*<<< orphan*/  autoneg; scalar_t__ address; struct ethtool_link_ksettings lks; } ;
struct TYPE_4__ {int (* init ) (struct xgbe_prv_data*) ;} ;
struct TYPE_5__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {int fec_ability; scalar_t__ tx_pause; scalar_t__ rx_pause; TYPE_3__ phy; int /*<<< orphan*/  pause_autoneg; TYPE_2__ phy_if; int /*<<< orphan*/  mdio_mmd; int /*<<< orphan*/  an_work; int /*<<< orphan*/  an_irq_work; int /*<<< orphan*/  an_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  Autoneg ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_MMD_PCS ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_10GBR_FECABLE ; 
 int MDIO_PMA_10GBR_FECABLE_ABLE ; 
 int MDIO_PMA_10GBR_FECABLE_ERRABLE ; 
 int /*<<< orphan*/  Pause ; 
 int /*<<< orphan*/  SPEED_UNKNOWN ; 
 scalar_t__ XGBE_ADV (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGBE_CLR_ADV (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGBE_LM_COPY (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGBE_SET_ADV (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  advertising ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_msg_drv (struct xgbe_prv_data*) ; 
 int stub1 (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  supported ; 
 int /*<<< orphan*/  xgbe_an_irq_work ; 
 int /*<<< orphan*/  xgbe_an_state_machine ; 
 int /*<<< orphan*/  xgbe_dump_phy_registers (struct xgbe_prv_data*) ; 
 int /*<<< orphan*/  xgbe_phy_best_advertised_speed (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_phy_init(struct xgbe_prv_data *pdata)
{
	struct ethtool_link_ksettings *lks = &pdata->phy.lks;
	int ret;

	mutex_init(&pdata->an_mutex);
	INIT_WORK(&pdata->an_irq_work, xgbe_an_irq_work);
	INIT_WORK(&pdata->an_work, xgbe_an_state_machine);
	pdata->mdio_mmd = MDIO_MMD_PCS;

	/* Check for FEC support */
	pdata->fec_ability = XMDIO_READ(pdata, MDIO_MMD_PMAPMD,
					MDIO_PMA_10GBR_FECABLE);
	pdata->fec_ability &= (MDIO_PMA_10GBR_FECABLE_ABLE |
			       MDIO_PMA_10GBR_FECABLE_ERRABLE);

	/* Setup the phy (including supported features) */
	ret = pdata->phy_if.phy_impl.init(pdata);
	if (ret)
		return ret;

	/* Copy supported link modes to advertising link modes */
	XGBE_LM_COPY(lks, advertising, lks, supported);

	pdata->phy.address = 0;

	if (XGBE_ADV(lks, Autoneg)) {
		pdata->phy.autoneg = AUTONEG_ENABLE;
		pdata->phy.speed = SPEED_UNKNOWN;
		pdata->phy.duplex = DUPLEX_UNKNOWN;
	} else {
		pdata->phy.autoneg = AUTONEG_DISABLE;
		pdata->phy.speed = xgbe_phy_best_advertised_speed(pdata);
		pdata->phy.duplex = DUPLEX_FULL;
	}

	pdata->phy.link = 0;

	pdata->phy.pause_autoneg = pdata->pause_autoneg;
	pdata->phy.tx_pause = pdata->tx_pause;
	pdata->phy.rx_pause = pdata->rx_pause;

	/* Fix up Flow Control advertising */
	XGBE_CLR_ADV(lks, Pause);
	XGBE_CLR_ADV(lks, Asym_Pause);

	if (pdata->rx_pause) {
		XGBE_SET_ADV(lks, Pause);
		XGBE_SET_ADV(lks, Asym_Pause);
	}

	if (pdata->tx_pause) {
		/* Equivalent to XOR of Asym_Pause */
		if (XGBE_ADV(lks, Asym_Pause))
			XGBE_CLR_ADV(lks, Asym_Pause);
		else
			XGBE_SET_ADV(lks, Asym_Pause);
	}

	if (netif_msg_drv(pdata))
		xgbe_dump_phy_registers(pdata);

	return 0;
}