#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ethtool_modinfo {int /*<<< orphan*/  eeprom_len; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/ * phy; } ;
struct bnx2x {TYPE_1__ link_params; } ;

/* Variables and functions */
 int BNX2X_MSG_ETHTOOL ; 
 int BNX2X_MSG_NVM ; 
 int /*<<< orphan*/  DP (int,char*) ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472_LEN ; 
 int /*<<< orphan*/  I2C_DEV_ADDR_A0 ; 
 int SFP_EEPROM_DDM_IMPLEMENTED ; 
 int SFP_EEPROM_DIAG_ADDR_CHANGE_REQ ; 
 int /*<<< orphan*/  SFP_EEPROM_DIAG_TYPE_ADDR ; 
 int /*<<< orphan*/  SFP_EEPROM_DIAG_TYPE_SIZE ; 
 int /*<<< orphan*/  SFP_EEPROM_SFF_8472_COMP_ADDR ; 
 int /*<<< orphan*/  SFP_EEPROM_SFF_8472_COMP_SIZE ; 
 int /*<<< orphan*/  bnx2x_acquire_phy_lock (struct bnx2x*) ; 
 int bnx2x_get_cur_phy_idx (struct bnx2x*) ; 
 int /*<<< orphan*/  bnx2x_is_nvm_accessible (struct bnx2x*) ; 
 int bnx2x_read_sfp_module_eeprom (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  bnx2x_release_phy_lock (struct bnx2x*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_get_module_info(struct net_device *dev,
				 struct ethtool_modinfo *modinfo)
{
	struct bnx2x *bp = netdev_priv(dev);
	int phy_idx, rc;
	u8 sff8472_comp, diag_type;

	if (!bnx2x_is_nvm_accessible(bp)) {
		DP(BNX2X_MSG_ETHTOOL | BNX2X_MSG_NVM,
		   "cannot access eeprom when the interface is down\n");
		return -EAGAIN;
	}
	phy_idx = bnx2x_get_cur_phy_idx(bp);
	bnx2x_acquire_phy_lock(bp);
	rc = bnx2x_read_sfp_module_eeprom(&bp->link_params.phy[phy_idx],
					  &bp->link_params,
					  I2C_DEV_ADDR_A0,
					  SFP_EEPROM_SFF_8472_COMP_ADDR,
					  SFP_EEPROM_SFF_8472_COMP_SIZE,
					  &sff8472_comp);
	bnx2x_release_phy_lock(bp);
	if (rc) {
		DP(BNX2X_MSG_ETHTOOL, "Failed reading SFF-8472 comp field\n");
		return -EINVAL;
	}

	bnx2x_acquire_phy_lock(bp);
	rc = bnx2x_read_sfp_module_eeprom(&bp->link_params.phy[phy_idx],
					  &bp->link_params,
					  I2C_DEV_ADDR_A0,
					  SFP_EEPROM_DIAG_TYPE_ADDR,
					  SFP_EEPROM_DIAG_TYPE_SIZE,
					  &diag_type);
	bnx2x_release_phy_lock(bp);
	if (rc) {
		DP(BNX2X_MSG_ETHTOOL, "Failed reading Diag Type field\n");
		return -EINVAL;
	}

	if (!sff8472_comp ||
	    (diag_type & SFP_EEPROM_DIAG_ADDR_CHANGE_REQ) ||
	    !(diag_type & SFP_EEPROM_DDM_IMPLEMENTED)) {
		modinfo->type = ETH_MODULE_SFF_8079;
		modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
	} else {
		modinfo->type = ETH_MODULE_SFF_8472;
		modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
	}
	return 0;
}