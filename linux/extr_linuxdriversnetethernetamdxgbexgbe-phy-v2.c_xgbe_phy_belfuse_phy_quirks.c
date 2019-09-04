#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xgbe_sfp_eeprom {int /*<<< orphan*/ * base; } ;
struct xgbe_prv_data {int an_again; int /*<<< orphan*/  netdev; struct xgbe_phy_data* phy_data; } ;
struct xgbe_phy_data {scalar_t__ port_mode; TYPE_1__* phydev; struct xgbe_sfp_eeprom sfp_eeprom; } ;
struct TYPE_3__ {unsigned int phy_id; int supported; int advertising; } ;

/* Variables and functions */
 int PHY_GBIT_FEATURES ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  XGBE_BEL_FUSE_PARTNO ; 
 int /*<<< orphan*/  XGBE_BEL_FUSE_VENDOR ; 
 scalar_t__ XGBE_PORT_MODE_SFP ; 
 size_t XGBE_SFP_BASE_VENDOR_NAME ; 
 int /*<<< orphan*/  XGBE_SFP_BASE_VENDOR_NAME_LEN ; 
 size_t XGBE_SFP_BASE_VENDOR_PN ; 
 int /*<<< orphan*/  XGBE_SFP_BASE_VENDOR_PN_LEN ; 
 int /*<<< orphan*/  drv ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_dbg (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int phy_read (TYPE_1__*,int) ; 
 int /*<<< orphan*/  phy_write (TYPE_1__*,int,int) ; 

__attribute__((used)) static bool xgbe_phy_belfuse_phy_quirks(struct xgbe_prv_data *pdata)
{
	struct xgbe_phy_data *phy_data = pdata->phy_data;
	struct xgbe_sfp_eeprom *sfp_eeprom = &phy_data->sfp_eeprom;
	unsigned int phy_id = phy_data->phydev->phy_id;
	int reg;

	if (phy_data->port_mode != XGBE_PORT_MODE_SFP)
		return false;

	if (memcmp(&sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_NAME],
		   XGBE_BEL_FUSE_VENDOR, XGBE_SFP_BASE_VENDOR_NAME_LEN))
		return false;

	/* For Bel-Fuse, use the extra AN flag */
	pdata->an_again = 1;

	if (memcmp(&sfp_eeprom->base[XGBE_SFP_BASE_VENDOR_PN],
		   XGBE_BEL_FUSE_PARTNO, XGBE_SFP_BASE_VENDOR_PN_LEN))
		return false;

	if ((phy_id & 0xfffffff0) != 0x03625d10)
		return false;

	/* Disable RGMII mode */
	phy_write(phy_data->phydev, 0x18, 0x7007);
	reg = phy_read(phy_data->phydev, 0x18);
	phy_write(phy_data->phydev, 0x18, reg & ~0x0080);

	/* Enable fiber register bank */
	phy_write(phy_data->phydev, 0x1c, 0x7c00);
	reg = phy_read(phy_data->phydev, 0x1c);
	reg &= 0x03ff;
	reg &= ~0x0001;
	phy_write(phy_data->phydev, 0x1c, 0x8000 | 0x7c00 | reg | 0x0001);

	/* Power down SerDes */
	reg = phy_read(phy_data->phydev, 0x00);
	phy_write(phy_data->phydev, 0x00, reg | 0x00800);

	/* Configure SGMII-to-Copper mode */
	phy_write(phy_data->phydev, 0x1c, 0x7c00);
	reg = phy_read(phy_data->phydev, 0x1c);
	reg &= 0x03ff;
	reg &= ~0x0006;
	phy_write(phy_data->phydev, 0x1c, 0x8000 | 0x7c00 | reg | 0x0004);

	/* Power up SerDes */
	reg = phy_read(phy_data->phydev, 0x00);
	phy_write(phy_data->phydev, 0x00, reg & ~0x00800);

	/* Enable copper register bank */
	phy_write(phy_data->phydev, 0x1c, 0x7c00);
	reg = phy_read(phy_data->phydev, 0x1c);
	reg &= 0x03ff;
	reg &= ~0x0001;
	phy_write(phy_data->phydev, 0x1c, 0x8000 | 0x7c00 | reg);

	/* Power up SerDes */
	reg = phy_read(phy_data->phydev, 0x00);
	phy_write(phy_data->phydev, 0x00, reg & ~0x00800);

	phy_data->phydev->supported = PHY_GBIT_FEATURES;
	phy_data->phydev->supported |= SUPPORTED_Pause | SUPPORTED_Asym_Pause;
	phy_data->phydev->advertising = phy_data->phydev->supported;

	netif_dbg(pdata, drv, pdata->netdev,
		  "BelFuse PHY quirk in place\n");

	return true;
}