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
struct hns_mac_cb {int max_speed; size_t phy_if; } ;
typedef  enum mac_mode { ____Placeholder_mac_mode } mac_mode ;

/* Variables and functions */
 int MAC_MODE_MII_100 ; 
 int MAC_MODE_XGMII_10000 ; 
#define  MAC_SPEED_100 130 
#define  MAC_SPEED_1000 129 
#define  MAC_SPEED_10000 128 
 int* g_mac_mode_100 ; 
 int* g_mac_mode_1000 ; 

__attribute__((used)) static enum mac_mode hns_get_enet_interface(const struct hns_mac_cb *mac_cb)
{
	switch (mac_cb->max_speed) {
	case MAC_SPEED_100:
		return g_mac_mode_100[mac_cb->phy_if];
	case MAC_SPEED_1000:
		return g_mac_mode_1000[mac_cb->phy_if];
	case MAC_SPEED_10000:
		return MAC_MODE_XGMII_10000;
	default:
		return MAC_MODE_MII_100;
	}
}