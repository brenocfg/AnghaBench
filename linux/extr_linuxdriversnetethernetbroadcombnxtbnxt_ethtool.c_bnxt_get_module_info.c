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
struct ethtool_modinfo {void* eeprom_len; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {scalar_t__ module_status; } ;
struct bnxt {int hwrm_spec_code; TYPE_1__ link_info; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8436 ; 
 void* ETH_MODULE_SFF_8436_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8472 ; 
 void* ETH_MODULE_SFF_8472_LEN ; 
 int /*<<< orphan*/  ETH_MODULE_SFF_8636 ; 
 void* ETH_MODULE_SFF_8636_LEN ; 
 int /*<<< orphan*/  I2C_DEV_ADDR_A0 ; 
 scalar_t__ PORT_PHY_QCFG_RESP_MODULE_STATUS_WARNINGMSG ; 
 int SFF_DIAG_SUPPORT_OFFSET ; 
#define  SFF_MODULE_ID_QSFP 131 
#define  SFF_MODULE_ID_QSFP28 130 
#define  SFF_MODULE_ID_QSFP_PLUS 129 
#define  SFF_MODULE_ID_SFP 128 
 int bnxt_read_sfp_module_eeprom_info (struct bnxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 struct bnxt* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnxt_get_module_info(struct net_device *dev,
				struct ethtool_modinfo *modinfo)
{
	u8 data[SFF_DIAG_SUPPORT_OFFSET + 1];
	struct bnxt *bp = netdev_priv(dev);
	int rc;

	/* No point in going further if phy status indicates
	 * module is not inserted or if it is powered down or
	 * if it is of type 10GBase-T
	 */
	if (bp->link_info.module_status >
		PORT_PHY_QCFG_RESP_MODULE_STATUS_WARNINGMSG)
		return -EOPNOTSUPP;

	/* This feature is not supported in older firmware versions */
	if (bp->hwrm_spec_code < 0x10202)
		return -EOPNOTSUPP;

	rc = bnxt_read_sfp_module_eeprom_info(bp, I2C_DEV_ADDR_A0, 0, 0,
					      SFF_DIAG_SUPPORT_OFFSET + 1,
					      data);
	if (!rc) {
		u8 module_id = data[0];
		u8 diag_supported = data[SFF_DIAG_SUPPORT_OFFSET];

		switch (module_id) {
		case SFF_MODULE_ID_SFP:
			modinfo->type = ETH_MODULE_SFF_8472;
			modinfo->eeprom_len = ETH_MODULE_SFF_8472_LEN;
			if (!diag_supported)
				modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
			break;
		case SFF_MODULE_ID_QSFP:
		case SFF_MODULE_ID_QSFP_PLUS:
			modinfo->type = ETH_MODULE_SFF_8436;
			modinfo->eeprom_len = ETH_MODULE_SFF_8436_LEN;
			break;
		case SFF_MODULE_ID_QSFP28:
			modinfo->type = ETH_MODULE_SFF_8636;
			modinfo->eeprom_len = ETH_MODULE_SFF_8636_LEN;
			break;
		default:
			rc = -EOPNOTSUPP;
			break;
		}
	}
	return rc;
}