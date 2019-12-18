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
struct port_info {int port_type; int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  mod_type; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ethtool_modinfo {int /*<<< orphan*/  eeprom_len; int /*<<< orphan*/  type; } ;
struct adapter {int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8079_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8436 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8436_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8636 ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8636_LEN ; 
#define  FW_PORT_TYPE_CR2_QSFP 135 
#define  FW_PORT_TYPE_CR4_QSFP 134 
#define  FW_PORT_TYPE_CR_QSFP 133 
#define  FW_PORT_TYPE_QSA 132 
#define  FW_PORT_TYPE_QSFP 131 
#define  FW_PORT_TYPE_QSFP_10G 130 
#define  FW_PORT_TYPE_SFP 129 
#define  FW_PORT_TYPE_SFP28 128 
 int /*<<< orphan*/  I2C_DEV_ADDR_A0 ; 
 int /*<<< orphan*/  SFF_8472_COMP_ADDR ; 
 int /*<<< orphan*/  SFF_8472_COMP_LEN ; 
 int /*<<< orphan*/  SFF_REV_ADDR ; 
 int /*<<< orphan*/  SFF_REV_LEN ; 
 int /*<<< orphan*/  SFP_DIAG_TYPE_ADDR ; 
 int /*<<< orphan*/  SFP_DIAG_TYPE_LEN ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int t4_i2c_rd (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t4_is_inserted_mod_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxgb4_get_module_info(struct net_device *dev,
				 struct ethtool_modinfo *modinfo)
{
	struct port_info *pi = netdev_priv(dev);
	u8 sff8472_comp, sff_diag_type, sff_rev;
	struct adapter *adapter = pi->adapter;
	int ret;

	if (!t4_is_inserted_mod_type(pi->mod_type))
		return -EINVAL;

	switch (pi->port_type) {
	case FW_PORT_TYPE_SFP:
	case FW_PORT_TYPE_QSA:
	case FW_PORT_TYPE_SFP28:
		ret = t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				I2C_DEV_ADDR_A0, SFF_8472_COMP_ADDR,
				SFF_8472_COMP_LEN, &sff8472_comp);
		if (ret)
			return ret;
		ret = t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				I2C_DEV_ADDR_A0, SFP_DIAG_TYPE_ADDR,
				SFP_DIAG_TYPE_LEN, &sff_diag_type);
		if (ret)
			return ret;

		if (!sff8472_comp || (sff_diag_type & 4)) {
			modinfo->type = ETH_MODULE_SFF_8079;
			modinfo->eeprom_len = ETH_MODULE_SFF_8079_LEN;
		} else {
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
		}
		break;

	case FW_PORT_TYPE_QSFP:
	case FW_PORT_TYPE_QSFP_10G:
	case FW_PORT_TYPE_CR_QSFP:
	case FW_PORT_TYPE_CR2_QSFP:
	case FW_PORT_TYPE_CR4_QSFP:
		ret = t4_i2c_rd(adapter, adapter->mbox, pi->tx_chan,
				I2C_DEV_ADDR_A0, SFF_REV_ADDR,
				SFF_REV_LEN, &sff_rev);
		/* For QSFP type ports, revision value >= 3
		 * means the SFP is 8636 compliant.
		 */
		if (ret)
			return ret;
		if (sff_rev >= 0x3) {
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
		} else {
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}