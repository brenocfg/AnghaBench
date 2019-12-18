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
typedef  int /*<<< orphan*/  u32 ;
struct hns_mac_cb {int mac_id; int /*<<< orphan*/  port_mode_off; TYPE_1__* dsaf_dev; } ;
typedef  int /*<<< orphan*/  phy_interface_t ;
struct TYPE_3__ {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 int AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 scalar_t__ HNS_DSAF_IS_DEBUG (TYPE_1__*) ; 
 int /*<<< orphan*/  HNS_MAC_HILINK3V2_REG ; 
 int /*<<< orphan*/  HNS_MAC_HILINK3_REG ; 
 int /*<<< orphan*/  HNS_MAC_HILINK4V2_REG ; 
 int /*<<< orphan*/  HNS_MAC_HILINK4_REG ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PHY_INTERFACE_MODE_XGMII ; 
 scalar_t__ dsaf_get_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsaf_read_sub (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static phy_interface_t hns_mac_get_phy_if(struct hns_mac_cb *mac_cb)
{
	u32 mode;
	u32 reg;
	bool is_ver1 = AE_IS_VER1(mac_cb->dsaf_dev->dsaf_ver);
	int mac_id = mac_cb->mac_id;
	phy_interface_t phy_if;

	if (is_ver1) {
		if (HNS_DSAF_IS_DEBUG(mac_cb->dsaf_dev))
			return PHY_INTERFACE_MODE_SGMII;

		if (mac_id >= 0 && mac_id <= 3)
			reg = HNS_MAC_HILINK4_REG;
		else
			reg = HNS_MAC_HILINK3_REG;
	} else{
		if (!HNS_DSAF_IS_DEBUG(mac_cb->dsaf_dev) && mac_id <= 3)
			reg = HNS_MAC_HILINK4V2_REG;
		else
			reg = HNS_MAC_HILINK3V2_REG;
	}

	mode = dsaf_read_sub(mac_cb->dsaf_dev, reg);
	if (dsaf_get_bit(mode, mac_cb->port_mode_off))
		phy_if = PHY_INTERFACE_MODE_XGMII;
	else
		phy_if = PHY_INTERFACE_MODE_SGMII;

	return phy_if;
}