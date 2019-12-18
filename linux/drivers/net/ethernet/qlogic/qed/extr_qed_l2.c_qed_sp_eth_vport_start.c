#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct qed_sp_init_data {int tpa_max_size; int tpa_min_size_to_cont; int tpa_min_size_to_start; int tpa_ipv4_en_flg; int tpa_ipv6_en_flg; int tpa_pkt_split_flg; int tpa_gro_consistent_flg; int /*<<< orphan*/  tpa_max_aggs_num; int /*<<< orphan*/  max_buff_num; int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_4__ {void* state; } ;
struct vport_start_ramrod_data {int ctl_frame_mac_check_en; int ctl_frame_ethtype_check_en; int /*<<< orphan*/  sw_fid; int /*<<< orphan*/  tx_switching_en; struct qed_sp_init_data tpa_param; TYPE_2__ rx_mode; int /*<<< orphan*/  untagged; int /*<<< orphan*/  drop_ttl0_en; int /*<<< orphan*/  inner_vlan_removal_en; int /*<<< orphan*/  handle_ptp_pkts; void* mtu; int /*<<< orphan*/  vport_id; } ;
struct TYPE_3__ {struct vport_start_ramrod_data vport_start; } ;
struct qed_spq_entry {TYPE_1__ ramrod; } ;
struct qed_sp_vport_start_params {int mtu; int tpa_mode; int /*<<< orphan*/  concrete_fid; int /*<<< orphan*/  check_ethtype; int /*<<< orphan*/  check_mac; int /*<<< orphan*/  tx_switching; int /*<<< orphan*/  max_buffers_per_cqe; int /*<<< orphan*/  only_untagged; int /*<<< orphan*/  drop_ttl0; int /*<<< orphan*/  remove_inner_vlan; int /*<<< orphan*/  handle_ptp_pkts; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  vport_id; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct eth_vport_tpa_param {int dummy; } ;
typedef  int /*<<< orphan*/  init_data ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ETH_RAMROD_VPORT_START ; 
 int /*<<< orphan*/  ETH_TPA_MAX_AGGS_NUM ; 
 int /*<<< orphan*/  ETH_VPORT_RX_MODE_MCAST_DROP_ALL ; 
 int /*<<< orphan*/  ETH_VPORT_RX_MODE_UCAST_DROP_ALL ; 
 int /*<<< orphan*/  PROTOCOLID_ETH ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
#define  QED_TPA_MODE_GRO 128 
 int /*<<< orphan*/  SET_FIELD (int,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_concrete_to_sw_fid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qed_fw_vport (struct qed_hwfn*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int /*<<< orphan*/  qed_spq_get_cid (struct qed_hwfn*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

int qed_sp_eth_vport_start(struct qed_hwfn *p_hwfn,
			   struct qed_sp_vport_start_params *p_params)
{
	struct vport_start_ramrod_data *p_ramrod = NULL;
	struct qed_spq_entry *p_ent =  NULL;
	struct qed_sp_init_data init_data;
	u8 abs_vport_id = 0;
	int rc = -EINVAL;
	u16 rx_mode = 0;

	rc = qed_fw_vport(p_hwfn, p_params->vport_id, &abs_vport_id);
	if (rc)
		return rc;

	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = qed_spq_get_cid(p_hwfn);
	init_data.opaque_fid = p_params->opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ETH_RAMROD_VPORT_START,
				 PROTOCOLID_ETH, &init_data);
	if (rc)
		return rc;

	p_ramrod		= &p_ent->ramrod.vport_start;
	p_ramrod->vport_id	= abs_vport_id;

	p_ramrod->mtu			= cpu_to_le16(p_params->mtu);
	p_ramrod->handle_ptp_pkts	= p_params->handle_ptp_pkts;
	p_ramrod->inner_vlan_removal_en	= p_params->remove_inner_vlan;
	p_ramrod->drop_ttl0_en		= p_params->drop_ttl0;
	p_ramrod->untagged		= p_params->only_untagged;

	SET_FIELD(rx_mode, ETH_VPORT_RX_MODE_UCAST_DROP_ALL, 1);
	SET_FIELD(rx_mode, ETH_VPORT_RX_MODE_MCAST_DROP_ALL, 1);

	p_ramrod->rx_mode.state = cpu_to_le16(rx_mode);

	/* TPA related fields */
	memset(&p_ramrod->tpa_param, 0, sizeof(struct eth_vport_tpa_param));

	p_ramrod->tpa_param.max_buff_num = p_params->max_buffers_per_cqe;

	switch (p_params->tpa_mode) {
	case QED_TPA_MODE_GRO:
		p_ramrod->tpa_param.tpa_max_aggs_num = ETH_TPA_MAX_AGGS_NUM;
		p_ramrod->tpa_param.tpa_max_size = (u16)-1;
		p_ramrod->tpa_param.tpa_min_size_to_cont = p_params->mtu / 2;
		p_ramrod->tpa_param.tpa_min_size_to_start = p_params->mtu / 2;
		p_ramrod->tpa_param.tpa_ipv4_en_flg = 1;
		p_ramrod->tpa_param.tpa_ipv6_en_flg = 1;
		p_ramrod->tpa_param.tpa_pkt_split_flg = 1;
		p_ramrod->tpa_param.tpa_gro_consistent_flg = 1;
		break;
	default:
		break;
	}

	p_ramrod->tx_switching_en = p_params->tx_switching;

	p_ramrod->ctl_frame_mac_check_en = !!p_params->check_mac;
	p_ramrod->ctl_frame_ethtype_check_en = !!p_params->check_ethtype;

	/* Software Function ID in hwfn (PFs are 0 - 15, VFs are 16 - 135) */
	p_ramrod->sw_fid = qed_concrete_to_sw_fid(p_hwfn->cdev,
						  p_params->concrete_fid);

	return qed_spq_post(p_hwfn, p_ent, NULL);
}