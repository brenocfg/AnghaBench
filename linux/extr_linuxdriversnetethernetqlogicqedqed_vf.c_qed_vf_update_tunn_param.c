#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int /*<<< orphan*/  b_mode_enabled; } ;
struct TYPE_5__ {int /*<<< orphan*/  port; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; } ;
struct qed_tunnel_info {TYPE_3__ ip_gre; TYPE_3__ l2_gre; TYPE_3__ ip_geneve; TYPE_3__ l2_geneve; TYPE_3__ vxlan; TYPE_2__ vxlan_port; TYPE_1__ geneve_port; } ;
struct qed_hwfn {int dummy; } ;
struct pfvf_update_tunn_param_tlv {int /*<<< orphan*/  vxlan_udp_port; int /*<<< orphan*/  geneve_udp_port; int /*<<< orphan*/  ipgre_clss; int /*<<< orphan*/  ipgre_mode; int /*<<< orphan*/  l2gre_clss; int /*<<< orphan*/  l2gre_mode; int /*<<< orphan*/  ipgeneve_clss; int /*<<< orphan*/  ipgeneve_mode; int /*<<< orphan*/  l2geneve_clss; int /*<<< orphan*/  l2geneve_mode; int /*<<< orphan*/  vxlan_clss; int /*<<< orphan*/  vxlan_mode; int /*<<< orphan*/  tunn_feature_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_VERBOSE (struct qed_hwfn*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QED_MODE_IPGENEVE_TUNN ; 
 int /*<<< orphan*/  QED_MODE_IPGRE_TUNN ; 
 int /*<<< orphan*/  QED_MODE_L2GENEVE_TUNN ; 
 int /*<<< orphan*/  QED_MODE_L2GRE_TUNN ; 
 int /*<<< orphan*/  QED_MODE_VXLAN_TUNN ; 
 int /*<<< orphan*/  QED_MSG_IOV ; 
 int /*<<< orphan*/  __qed_vf_update_tunn_param (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qed_vf_update_tunn_param(struct qed_hwfn *p_hwfn,
				     struct qed_tunnel_info *p_tun,
				     struct pfvf_update_tunn_param_tlv *p_resp)
{
	/* Update mode and classes provided by PF */
	u16 feat_mask = p_resp->tunn_feature_mask;

	__qed_vf_update_tunn_param(&p_tun->vxlan, feat_mask,
				   p_resp->vxlan_mode, p_resp->vxlan_clss,
				   QED_MODE_VXLAN_TUNN);
	__qed_vf_update_tunn_param(&p_tun->l2_geneve, feat_mask,
				   p_resp->l2geneve_mode,
				   p_resp->l2geneve_clss,
				   QED_MODE_L2GENEVE_TUNN);
	__qed_vf_update_tunn_param(&p_tun->ip_geneve, feat_mask,
				   p_resp->ipgeneve_mode,
				   p_resp->ipgeneve_clss,
				   QED_MODE_IPGENEVE_TUNN);
	__qed_vf_update_tunn_param(&p_tun->l2_gre, feat_mask,
				   p_resp->l2gre_mode, p_resp->l2gre_clss,
				   QED_MODE_L2GRE_TUNN);
	__qed_vf_update_tunn_param(&p_tun->ip_gre, feat_mask,
				   p_resp->ipgre_mode, p_resp->ipgre_clss,
				   QED_MODE_IPGRE_TUNN);
	p_tun->geneve_port.port = p_resp->geneve_udp_port;
	p_tun->vxlan_port.port = p_resp->vxlan_udp_port;

	DP_VERBOSE(p_hwfn, QED_MSG_IOV,
		   "tunn mode: vxlan=0x%x, l2geneve=0x%x, ipgeneve=0x%x, l2gre=0x%x, ipgre=0x%x",
		   p_tun->vxlan.b_mode_enabled, p_tun->l2_geneve.b_mode_enabled,
		   p_tun->ip_geneve.b_mode_enabled,
		   p_tun->l2_gre.b_mode_enabled, p_tun->ip_gre.b_mode_enabled);
}