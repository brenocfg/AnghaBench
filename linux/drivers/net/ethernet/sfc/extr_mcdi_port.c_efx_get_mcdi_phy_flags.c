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
typedef  int u32 ;
struct efx_nic {int phy_mode; struct efx_mcdi_phy_data* phy_data; } ;
struct efx_mcdi_phy_data {int flags; } ;
typedef  enum efx_phy_mode { ____Placeholder_efx_phy_mode } efx_phy_mode ;

/* Variables and functions */
 int MC_CMD_GET_PHY_CFG_OUT_LOWPOWER_LBN ; 
 int MC_CMD_GET_PHY_CFG_OUT_POWEROFF_LBN ; 
 int MC_CMD_GET_PHY_CFG_OUT_TXDIS_LBN ; 
 int MC_CMD_SET_LINK_IN_LOWPOWER_LBN ; 
 int MC_CMD_SET_LINK_IN_POWEROFF_LBN ; 
 int MC_CMD_SET_LINK_IN_TXDIS_LBN ; 
 int PHY_MODE_LOW_POWER ; 
 int PHY_MODE_OFF ; 
 int PHY_MODE_TX_DISABLED ; 

__attribute__((used)) static u32 efx_get_mcdi_phy_flags(struct efx_nic *efx)
{
	struct efx_mcdi_phy_data *phy_cfg = efx->phy_data;
	enum efx_phy_mode mode, supported;
	u32 flags;

	/* TODO: Advertise the capabilities supported by this PHY */
	supported = 0;
	if (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_TXDIS_LBN))
		supported |= PHY_MODE_TX_DISABLED;
	if (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_LOWPOWER_LBN))
		supported |= PHY_MODE_LOW_POWER;
	if (phy_cfg->flags & (1 << MC_CMD_GET_PHY_CFG_OUT_POWEROFF_LBN))
		supported |= PHY_MODE_OFF;

	mode = efx->phy_mode & supported;

	flags = 0;
	if (mode & PHY_MODE_TX_DISABLED)
		flags |= (1 << MC_CMD_SET_LINK_IN_TXDIS_LBN);
	if (mode & PHY_MODE_LOW_POWER)
		flags |= (1 << MC_CMD_SET_LINK_IN_LOWPOWER_LBN);
	if (mode & PHY_MODE_OFF)
		flags |= (1 << MC_CMD_SET_LINK_IN_POWEROFF_LBN);

	return flags;
}