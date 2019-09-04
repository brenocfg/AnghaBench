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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  update_tx_mode_config; int /*<<< orphan*/  update_rx_mode_config; } ;
struct qed_sp_vport_update_params {int /*<<< orphan*/  sge_tpa_params; int /*<<< orphan*/  rss_params; TYPE_1__ accept_flags; int /*<<< orphan*/  update_approx_mcast_flg; int /*<<< orphan*/  update_accept_any_vlan_flg; int /*<<< orphan*/  update_inner_vlan_removal_flg; int /*<<< orphan*/  update_tx_switching_flg; int /*<<< orphan*/  update_vport_active_tx_flg; int /*<<< orphan*/  update_vport_active_rx_flg; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
#define  CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN 135 
#define  CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM 134 
#define  CHANNEL_TLV_VPORT_UPDATE_ACTIVATE 133 
#define  CHANNEL_TLV_VPORT_UPDATE_MCAST 132 
#define  CHANNEL_TLV_VPORT_UPDATE_RSS 131 
#define  CHANNEL_TLV_VPORT_UPDATE_SGE_TPA 130 
#define  CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH 129 
#define  CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP 128 
 int /*<<< orphan*/  DP_INFO (struct qed_hwfn*,char*,int) ; 

__attribute__((used)) static bool
qed_vf_handle_vp_update_is_needed(struct qed_hwfn *p_hwfn,
				  struct qed_sp_vport_update_params *p_data,
				  u16 tlv)
{
	switch (tlv) {
	case CHANNEL_TLV_VPORT_UPDATE_ACTIVATE:
		return !!(p_data->update_vport_active_rx_flg ||
			  p_data->update_vport_active_tx_flg);
	case CHANNEL_TLV_VPORT_UPDATE_TX_SWITCH:
		return !!p_data->update_tx_switching_flg;
	case CHANNEL_TLV_VPORT_UPDATE_VLAN_STRIP:
		return !!p_data->update_inner_vlan_removal_flg;
	case CHANNEL_TLV_VPORT_UPDATE_ACCEPT_ANY_VLAN:
		return !!p_data->update_accept_any_vlan_flg;
	case CHANNEL_TLV_VPORT_UPDATE_MCAST:
		return !!p_data->update_approx_mcast_flg;
	case CHANNEL_TLV_VPORT_UPDATE_ACCEPT_PARAM:
		return !!(p_data->accept_flags.update_rx_mode_config ||
			  p_data->accept_flags.update_tx_mode_config);
	case CHANNEL_TLV_VPORT_UPDATE_RSS:
		return !!p_data->rss_params;
	case CHANNEL_TLV_VPORT_UPDATE_SGE_TPA:
		return !!p_data->sge_tpa_params;
	default:
		DP_INFO(p_hwfn, "Unexpected vport-update TLV[%d]\n",
			tlv);
		return false;
	}
}