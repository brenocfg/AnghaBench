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
struct TYPE_3__ {int /*<<< orphan*/  (* an_advertising ) (struct xgbe_prv_data*,struct ethtool_link_ksettings*) ;} ;
struct TYPE_4__ {TYPE_1__ phy_impl; } ;
struct xgbe_prv_data {int an_mode; int /*<<< orphan*/  netdev; TYPE_2__ phy_if; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  Asym_Pause ; 
 int /*<<< orphan*/  MDIO_MMD_VEND2 ; 
 int /*<<< orphan*/  MDIO_VEND2_AN_ADVERTISE ; 
 int /*<<< orphan*/  MDIO_VEND2_AN_CTRL ; 
 int /*<<< orphan*/  Pause ; 
 scalar_t__ XGBE_ADV (struct ethtool_link_ksettings*,int /*<<< orphan*/ ) ; 
 unsigned int XGBE_AN_CL37_FD_MASK ; 
 unsigned int XGBE_AN_CL37_HD_MASK ; 
 unsigned int XGBE_AN_CL37_MII_CTRL_8BIT ; 
 unsigned int XGBE_AN_CL37_PCS_MODE_BASEX ; 
 unsigned int XGBE_AN_CL37_PCS_MODE_MASK ; 
 unsigned int XGBE_AN_CL37_PCS_MODE_SGMII ; 
 unsigned int XGBE_AN_CL37_TX_CONFIG_MASK ; 
#define  XGBE_AN_MODE_CL37 129 
#define  XGBE_AN_MODE_CL37_SGMII 128 
 unsigned int XMDIO_READ (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMDIO_WRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stub1 (struct xgbe_prv_data*,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static void xgbe_an37_init(struct xgbe_prv_data *pdata)
{
	struct ethtool_link_ksettings lks;
	unsigned int reg;

	pdata->phy_if.phy_impl.an_advertising(pdata, &lks);

	/* Set up Advertisement register */
	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVERTISE);
	if (XGBE_ADV(&lks, Pause))
		reg |= 0x100;
	else
		reg &= ~0x100;

	if (XGBE_ADV(&lks, Asym_Pause))
		reg |= 0x80;
	else
		reg &= ~0x80;

	/* Full duplex, but not half */
	reg |= XGBE_AN_CL37_FD_MASK;
	reg &= ~XGBE_AN_CL37_HD_MASK;

	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_ADVERTISE, reg);

	/* Set up the Control register */
	reg = XMDIO_READ(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL);
	reg &= ~XGBE_AN_CL37_TX_CONFIG_MASK;
	reg &= ~XGBE_AN_CL37_PCS_MODE_MASK;

	switch (pdata->an_mode) {
	case XGBE_AN_MODE_CL37:
		reg |= XGBE_AN_CL37_PCS_MODE_BASEX;
		break;
	case XGBE_AN_MODE_CL37_SGMII:
		reg |= XGBE_AN_CL37_PCS_MODE_SGMII;
		break;
	default:
		break;
	}

	reg |= XGBE_AN_CL37_MII_CTRL_8BIT;

	XMDIO_WRITE(pdata, MDIO_MMD_VEND2, MDIO_VEND2_AN_CTRL, reg);

	netif_dbg(pdata, link, pdata->netdev, "CL37 AN (%s) initialized\n",
		  (pdata->an_mode == XGBE_AN_MODE_CL37) ? "BaseX" : "SGMII");
}