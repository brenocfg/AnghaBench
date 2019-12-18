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
typedef  int /*<<< orphan*/  u16 ;
struct qed_hwfn {int dummy; } ;
typedef  enum qed_iov_vport_update_flag { ____Placeholder_qed_iov_vport_update_flag } qed_iov_vport_update_flag ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_ACTIVATE ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_MCAST ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_RSS ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_SGE_TPA ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH ; 
 int /*<<< orphan*/  CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP ; 
#define  QED_IOV_VP_UPDATE_ACCEPT_ANY_VLAN 135 
#define  QED_IOV_VP_UPDATE_ACCEPT_PARAM 134 
#define  QED_IOV_VP_UPDATE_ACTIVATE 133 
#define  QED_IOV_VP_UPDATE_MCAST 132 
#define  QED_IOV_VP_UPDATE_RSS 131 
#define  QED_IOV_VP_UPDATE_SGE_TPA 130 
#define  QED_IOV_VP_UPDATE_TX_SWITCH 129 
#define  QED_IOV_VP_UPDATE_VLAN_STRIP 128 

__attribute__((used)) static u16 qed_iov_vport_to_tlv(struct qed_hwfn *p_hwfn,
				enum qed_iov_vport_update_flag flag)
{
	switch (flag) {
	case QED_IOV_VP_UPDATE_ACTIVATE:
		return CHANNEL_TLV_VPORT_UPDATE_ACTIVATE;
	case QED_IOV_VP_UPDATE_VLAN_STRIP:
		return CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP;
	case QED_IOV_VP_UPDATE_TX_SWITCH:
		return CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH;
	case QED_IOV_VP_UPDATE_MCAST:
		return CHANNEL_TLV_VPORT_UPDATE_MCAST;
	case QED_IOV_VP_UPDATE_ACCEPT_PARAM:
		return CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM;
	case QED_IOV_VP_UPDATE_RSS:
		return CHANNEL_TLV_VPORT_UPDATE_RSS;
	case QED_IOV_VP_UPDATE_ACCEPT_ANY_VLAN:
		return CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN;
	case QED_IOV_VP_UPDATE_SGE_TPA:
		return CHANNEL_TLV_VPORT_UPDATE_SGE_TPA;
	default:
		return 0;
	}
}