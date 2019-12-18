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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct link_params {struct bnx2x* bp; } ;
struct bnx2x_phy {int type; } ;
struct bnx2x {int dummy; } ;
typedef  int (* read_sfp_module_eeprom_func_p ) (struct bnx2x_phy*,struct link_params*,int,scalar_t__,int,int*,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,int) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722 131 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726 130 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727 129 
#define  PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT 128 
 scalar_t__ SFP_EEPROM_PAGE_SIZE ; 
 int bnx2x_8726_read_sfp_module_eeprom (struct bnx2x_phy*,struct link_params*,int,scalar_t__,int,int*,int /*<<< orphan*/ ) ; 
 int bnx2x_8727_read_sfp_module_eeprom (struct bnx2x_phy*,struct link_params*,int,scalar_t__,int,int*,int /*<<< orphan*/ ) ; 
 int bnx2x_warpcore_read_sfp_module_eeprom (struct bnx2x_phy*,struct link_params*,int,scalar_t__,int,int*,int /*<<< orphan*/ ) ; 

int bnx2x_read_sfp_module_eeprom(struct bnx2x_phy *phy,
				 struct link_params *params, u8 dev_addr,
				 u16 addr, u16 byte_cnt, u8 *o_buf)
{
	int rc = 0;
	struct bnx2x *bp = params->bp;
	u8 xfer_size;
	u8 *user_data = o_buf;
	read_sfp_module_eeprom_func_p read_func;

	if ((dev_addr != 0xa0) && (dev_addr != 0xa2)) {
		DP(NETIF_MSG_LINK, "invalid dev_addr 0x%x\n", dev_addr);
		return -EINVAL;
	}

	switch (phy->type) {
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8726:
		read_func = bnx2x_8726_read_sfp_module_eeprom;
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8727:
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_BCM8722:
		read_func = bnx2x_8727_read_sfp_module_eeprom;
		break;
	case PORT_HW_CFG_XGXS_EXT_PHY_TYPE_DIRECT:
		read_func = bnx2x_warpcore_read_sfp_module_eeprom;
		break;
	default:
		return -EOPNOTSUPP;
	}

	while (!rc && (byte_cnt > 0)) {
		xfer_size = (byte_cnt > SFP_EEPROM_PAGE_SIZE) ?
			SFP_EEPROM_PAGE_SIZE : byte_cnt;
		rc = read_func(phy, params, dev_addr, addr, xfer_size,
			       user_data, 0);
		byte_cnt -= xfer_size;
		user_data += xfer_size;
		addr += xfer_size;
	}
	return rc;
}