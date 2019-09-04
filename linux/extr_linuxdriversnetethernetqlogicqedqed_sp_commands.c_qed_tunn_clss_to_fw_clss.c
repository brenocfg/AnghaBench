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
typedef  enum tunnel_clss { ____Placeholder_tunnel_clss } tunnel_clss ;

/* Variables and functions */
#define  QED_TUNN_CLSS_INNER_MAC_VLAN 132 
#define  QED_TUNN_CLSS_INNER_MAC_VNI 131 
#define  QED_TUNN_CLSS_MAC_VLAN 130 
#define  QED_TUNN_CLSS_MAC_VLAN_DUAL_STAGE 129 
#define  QED_TUNN_CLSS_MAC_VNI 128 
 int TUNNEL_CLSS_INNER_MAC_VLAN ; 
 int TUNNEL_CLSS_INNER_MAC_VNI ; 
 int TUNNEL_CLSS_MAC_VLAN ; 
 int TUNNEL_CLSS_MAC_VLAN_DUAL_STAGE ; 
 int TUNNEL_CLSS_MAC_VNI ; 

__attribute__((used)) static enum tunnel_clss qed_tunn_clss_to_fw_clss(u8 type)
{
	switch (type) {
	case QED_TUNN_CLSS_MAC_VLAN:
		return TUNNEL_CLSS_MAC_VLAN;
	case QED_TUNN_CLSS_MAC_VNI:
		return TUNNEL_CLSS_MAC_VNI;
	case QED_TUNN_CLSS_INNER_MAC_VLAN:
		return TUNNEL_CLSS_INNER_MAC_VLAN;
	case QED_TUNN_CLSS_INNER_MAC_VNI:
		return TUNNEL_CLSS_INNER_MAC_VNI;
	case QED_TUNN_CLSS_MAC_VLAN_DUAL_STAGE:
		return TUNNEL_CLSS_MAC_VLAN_DUAL_STAGE;
	default:
		return TUNNEL_CLSS_MAC_VLAN;
	}
}