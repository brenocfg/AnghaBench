#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcp_offload_params_opt2 {void* ka_interval; void* max_rt_time; void* ka_timeout; int /*<<< orphan*/  ka_max_probe_cnt; void* cwnd; int /*<<< orphan*/  syn_phy_addr_hi; int /*<<< orphan*/  syn_phy_addr_lo; void* syn_ip_payload_length; int /*<<< orphan*/  connect_mode; int /*<<< orphan*/  rcv_wnd_scale; void* mss; void* local_port; void* remote_port; int /*<<< orphan*/  tos_or_tc; int /*<<< orphan*/  ttl; void* flow_label; void** local_ip; void** remote_ip; int /*<<< orphan*/  ip_version; void* flags; void* vlan_id; void* remote_mac_addr_lo; void* remote_mac_addr_mid; void* remote_mac_addr_hi; void* local_mac_addr_lo; void* local_mac_addr_mid; void* local_mac_addr_hi; } ;
struct tcp_offload_params {int /*<<< orphan*/  connect_mode; int /*<<< orphan*/  ack_frequency; void* da_timeout_value; int /*<<< orphan*/  rcv_wnd_scale; int /*<<< orphan*/  snd_wnd_scale; void* mss; void* local_port; void* remote_port; int /*<<< orphan*/  tos_or_tc; int /*<<< orphan*/  ttl; void* initial_rcv_wnd; void* max_rt_time; void* ka_interval; void* ka_timeout; void* flow_label; int /*<<< orphan*/  rt_cnt; int /*<<< orphan*/  ka_probe_cnt; int /*<<< orphan*/  snd_wnd_probe_cnt; int /*<<< orphan*/  dup_ack_cnt; void* rt_timeout_delta; void* ka_timeout_delta; void* total_rt; void* ts_recent_age; void* ts_recent; void* rtt_var; void* srtt; void* ss_thresh; void* cwnd; void* snd_wl1; void* rcv_wnd; void* snd_wnd; void* snd_max; void* snd_next; void* snd_una; void* rcv_next; int /*<<< orphan*/  dup_ack_theshold; int /*<<< orphan*/  ka_max_probe_cnt; void** local_ip; void** remote_ip; int /*<<< orphan*/  ip_version; void* flags; void* vlan_id; void* remote_mac_addr_lo; void* remote_mac_addr_mid; void* remote_mac_addr_hi; void* local_mac_addr_lo; void* local_mac_addr_mid; void* local_mac_addr_hi; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; void* stat_sn; int /*<<< orphan*/  default_cq; void* initial_ack; int /*<<< orphan*/  uhq_pbl_addr; int /*<<< orphan*/  xhq_pbl_addr; int /*<<< orphan*/  r2tq_pbl_addr; int /*<<< orphan*/  sq_pbl_addr; void* physical_q1; void* physical_q0; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  op_code; } ;
struct iscsi_spe_conn_offload {struct tcp_offload_params tcp; TYPE_4__ iscsi; void* fw_cid; void* conn_id; TYPE_3__ hdr; } ;
struct TYPE_6__ {struct iscsi_spe_conn_offload iscsi_conn_offload; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_spq_comp_cb {int dummy; } ;
struct qed_sp_init_data {int comp_mode; struct qed_spq_comp_cb* p_comp_data; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_iscsi_conn {int /*<<< orphan*/  ka_interval; int /*<<< orphan*/  max_rt_time; int /*<<< orphan*/  ka_timeout; int /*<<< orphan*/  ka_probe_cnt; int /*<<< orphan*/  cwnd; int /*<<< orphan*/  syn_phy_addr; int /*<<< orphan*/  syn_ip_payload_length; int /*<<< orphan*/  connect_mode; int /*<<< orphan*/  rcv_wnd_scale; int /*<<< orphan*/  mss; int /*<<< orphan*/  local_port; int /*<<< orphan*/  remote_port; int /*<<< orphan*/  tos_or_tc; int /*<<< orphan*/  ttl; int /*<<< orphan*/  flow_label; int /*<<< orphan*/ * local_ip; int /*<<< orphan*/ * remote_ip; int /*<<< orphan*/  ip_version; int /*<<< orphan*/  tcp_flags; int /*<<< orphan*/  vlan_id; scalar_t__ remote_mac; scalar_t__ local_mac; int /*<<< orphan*/  ack_frequency; int /*<<< orphan*/  da_timeout_value; int /*<<< orphan*/  snd_wnd_scale; int /*<<< orphan*/  initial_rcv_wnd; int /*<<< orphan*/  rt_cnt; int /*<<< orphan*/  snd_wnd_probe_cnt; int /*<<< orphan*/  dup_ack_cnt; int /*<<< orphan*/  rt_timeout_delta; int /*<<< orphan*/  ka_timeout_delta; int /*<<< orphan*/  total_rt; int /*<<< orphan*/  ts_recent_age; int /*<<< orphan*/  ts_recent; int /*<<< orphan*/  rtt_var; int /*<<< orphan*/  srtt; int /*<<< orphan*/  ss_thresh; int /*<<< orphan*/  snd_wl1; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  snd_max; int /*<<< orphan*/  snd_next; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  rcv_next; int /*<<< orphan*/  dup_ack_theshold; int /*<<< orphan*/  ka_max_probe_cnt; int /*<<< orphan*/  stat_sn; int /*<<< orphan*/  default_cq; int /*<<< orphan*/  offl_flags; int /*<<< orphan*/  initial_ack; int /*<<< orphan*/  uhq; int /*<<< orphan*/  xhq; int /*<<< orphan*/  r2tq; int /*<<< orphan*/  sq_pbl_addr; int /*<<< orphan*/  icid; int /*<<< orphan*/  conn_id; int /*<<< orphan*/  layer_code; void* physical_q1; void* physical_q0; } ;
struct TYPE_5__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_1__ hw_info; } ;
struct iscsi_spe_conn_offload_option2 {struct tcp_offload_params_opt2 tcp; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_HI_LE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_LO_LE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISCSI_CONN_OFFLOAD_PARAMS_TCP_ON_CHIP_1B ; 
 int /*<<< orphan*/  ISCSI_RAMROD_CMD_ID_OFFLOAD_CONN ; 
 int /*<<< orphan*/  ISCSI_SLOW_PATH_HDR_LAYER_CODE ; 
 int /*<<< orphan*/  PQ_FLAGS_ACK ; 
 int /*<<< orphan*/  PQ_FLAGS_OFLD ; 
 int /*<<< orphan*/  PROTOCOLID_ISCSI ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_chain_get_pbl_phys (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_get_cm_pq_idx (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 void* swab16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qed_sp_iscsi_conn_offload(struct qed_hwfn *p_hwfn,
				     struct qed_iscsi_conn *p_conn,
				     enum spq_mode comp_mode,
				     struct qed_spq_comp_cb *p_comp_addr)
{
	struct iscsi_spe_conn_offload *p_ramrod = NULL;
	struct tcp_offload_params_opt2 *p_tcp2 = NULL;
	struct tcp_offload_params *p_tcp = NULL;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	dma_addr_t r2tq_pbl_addr;
	dma_addr_t xhq_pbl_addr;
	dma_addr_t uhq_pbl_addr;
	u16 physical_q;
	int rc = 0;
	u32 dval;
	u16 wval;
	u16 *p;
	u8 i;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 ISCSI_RAMROD_CMD_ID_OFFLOAD_CONN,
				 PROTOCOLID_ISCSI, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.iscsi_conn_offload;

	/* Transmission PQ is the first of the PF */
	physical_q = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_conn->physical_q0 = cpu_to_le16(physical_q);
	p_ramrod->iscsi.physical_q0 = cpu_to_le16(physical_q);

	/* iSCSI Pure-ACK PQ */
	physical_q = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_ACK);
	p_conn->physical_q1 = cpu_to_le16(physical_q);
	p_ramrod->iscsi.physical_q1 = cpu_to_le16(physical_q);

	p_ramrod->hdr.op_code = ISCSI_RAMROD_CMD_ID_OFFLOAD_CONN;
	SET_FIELD(p_ramrod->hdr.flags, ISCSI_SLOW_PATH_HDR_LAYER_CODE,
		  p_conn->layer_code);

	p_ramrod->conn_id = cpu_to_le16(p_conn->conn_id);
	p_ramrod->fw_cid = cpu_to_le32(p_conn->icid);

	DMA_REGPAIR_LE(p_ramrod->iscsi.sq_pbl_addr, p_conn->sq_pbl_addr);

	r2tq_pbl_addr = qed_chain_get_pbl_phys(&p_conn->r2tq);
	DMA_REGPAIR_LE(p_ramrod->iscsi.r2tq_pbl_addr, r2tq_pbl_addr);

	xhq_pbl_addr = qed_chain_get_pbl_phys(&p_conn->xhq);
	DMA_REGPAIR_LE(p_ramrod->iscsi.xhq_pbl_addr, xhq_pbl_addr);

	uhq_pbl_addr = qed_chain_get_pbl_phys(&p_conn->uhq);
	DMA_REGPAIR_LE(p_ramrod->iscsi.uhq_pbl_addr, uhq_pbl_addr);

	p_ramrod->iscsi.initial_ack = cpu_to_le32(p_conn->initial_ack);
	p_ramrod->iscsi.flags = p_conn->offl_flags;
	p_ramrod->iscsi.default_cq = p_conn->default_cq;
	p_ramrod->iscsi.stat_sn = cpu_to_le32(p_conn->stat_sn);

	if (!GET_FIELD(p_ramrod->iscsi.flags,
		       ISCSI_CONN_OFFLOAD_PARAMS_TCP_ON_CHIP_1B)) {
		p_tcp = &p_ramrod->tcp;

		p = (u16 *)p_conn->local_mac;
		p_tcp->local_mac_addr_hi = swab16(get_unaligned(p));
		p_tcp->local_mac_addr_mid = swab16(get_unaligned(p + 1));
		p_tcp->local_mac_addr_lo = swab16(get_unaligned(p + 2));

		p = (u16 *)p_conn->remote_mac;
		p_tcp->remote_mac_addr_hi = swab16(get_unaligned(p));
		p_tcp->remote_mac_addr_mid = swab16(get_unaligned(p + 1));
		p_tcp->remote_mac_addr_lo = swab16(get_unaligned(p + 2));

		p_tcp->vlan_id = cpu_to_le16(p_conn->vlan_id);

		p_tcp->flags = cpu_to_le16(p_conn->tcp_flags);
		p_tcp->ip_version = p_conn->ip_version;
		for (i = 0; i < 4; i++) {
			dval = p_conn->remote_ip[i];
			p_tcp->remote_ip[i] = cpu_to_le32(dval);
			dval = p_conn->local_ip[i];
			p_tcp->local_ip[i] = cpu_to_le32(dval);
		}
		p_tcp->ka_max_probe_cnt = p_conn->ka_max_probe_cnt;
		p_tcp->dup_ack_theshold = p_conn->dup_ack_theshold;

		p_tcp->rcv_next = cpu_to_le32(p_conn->rcv_next);
		p_tcp->snd_una = cpu_to_le32(p_conn->snd_una);
		p_tcp->snd_next = cpu_to_le32(p_conn->snd_next);
		p_tcp->snd_max = cpu_to_le32(p_conn->snd_max);
		p_tcp->snd_wnd = cpu_to_le32(p_conn->snd_wnd);
		p_tcp->rcv_wnd = cpu_to_le32(p_conn->rcv_wnd);
		p_tcp->snd_wl1 = cpu_to_le32(p_conn->snd_wl1);
		p_tcp->cwnd = cpu_to_le32(p_conn->cwnd);
		p_tcp->ss_thresh = cpu_to_le32(p_conn->ss_thresh);
		p_tcp->srtt = cpu_to_le16(p_conn->srtt);
		p_tcp->rtt_var = cpu_to_le16(p_conn->rtt_var);
		p_tcp->ts_recent = cpu_to_le32(p_conn->ts_recent);
		p_tcp->ts_recent_age = cpu_to_le32(p_conn->ts_recent_age);
		p_tcp->total_rt = cpu_to_le32(p_conn->total_rt);
		dval = p_conn->ka_timeout_delta;
		p_tcp->ka_timeout_delta = cpu_to_le32(dval);
		dval = p_conn->rt_timeout_delta;
		p_tcp->rt_timeout_delta = cpu_to_le32(dval);
		p_tcp->dup_ack_cnt = p_conn->dup_ack_cnt;
		p_tcp->snd_wnd_probe_cnt = p_conn->snd_wnd_probe_cnt;
		p_tcp->ka_probe_cnt = p_conn->ka_probe_cnt;
		p_tcp->rt_cnt = p_conn->rt_cnt;
		p_tcp->flow_label = cpu_to_le32(p_conn->flow_label);
		p_tcp->ka_timeout = cpu_to_le32(p_conn->ka_timeout);
		p_tcp->ka_interval = cpu_to_le32(p_conn->ka_interval);
		p_tcp->max_rt_time = cpu_to_le32(p_conn->max_rt_time);
		dval = p_conn->initial_rcv_wnd;
		p_tcp->initial_rcv_wnd = cpu_to_le32(dval);
		p_tcp->ttl = p_conn->ttl;
		p_tcp->tos_or_tc = p_conn->tos_or_tc;
		p_tcp->remote_port = cpu_to_le16(p_conn->remote_port);
		p_tcp->local_port = cpu_to_le16(p_conn->local_port);
		p_tcp->mss = cpu_to_le16(p_conn->mss);
		p_tcp->snd_wnd_scale = p_conn->snd_wnd_scale;
		p_tcp->rcv_wnd_scale = p_conn->rcv_wnd_scale;
		wval = p_conn->da_timeout_value;
		p_tcp->da_timeout_value = cpu_to_le16(wval);
		p_tcp->ack_frequency = p_conn->ack_frequency;
		p_tcp->connect_mode = p_conn->connect_mode;
	} else {
		p_tcp2 =
		    &((struct iscsi_spe_conn_offload_option2 *)p_ramrod)->tcp;

		p = (u16 *)p_conn->local_mac;
		p_tcp2->local_mac_addr_hi = swab16(get_unaligned(p));
		p_tcp2->local_mac_addr_mid = swab16(get_unaligned(p + 1));
		p_tcp2->local_mac_addr_lo = swab16(get_unaligned(p + 2));

		p = (u16 *)p_conn->remote_mac;
		p_tcp2->remote_mac_addr_hi = swab16(get_unaligned(p));
		p_tcp2->remote_mac_addr_mid = swab16(get_unaligned(p + 1));
		p_tcp2->remote_mac_addr_lo = swab16(get_unaligned(p + 2));

		p_tcp2->vlan_id = cpu_to_le16(p_conn->vlan_id);
		p_tcp2->flags = cpu_to_le16(p_conn->tcp_flags);

		p_tcp2->ip_version = p_conn->ip_version;
		for (i = 0; i < 4; i++) {
			dval = p_conn->remote_ip[i];
			p_tcp2->remote_ip[i] = cpu_to_le32(dval);
			dval = p_conn->local_ip[i];
			p_tcp2->local_ip[i] = cpu_to_le32(dval);
		}

		p_tcp2->flow_label = cpu_to_le32(p_conn->flow_label);
		p_tcp2->ttl = p_conn->ttl;
		p_tcp2->tos_or_tc = p_conn->tos_or_tc;
		p_tcp2->remote_port = cpu_to_le16(p_conn->remote_port);
		p_tcp2->local_port = cpu_to_le16(p_conn->local_port);
		p_tcp2->mss = cpu_to_le16(p_conn->mss);
		p_tcp2->rcv_wnd_scale = p_conn->rcv_wnd_scale;
		p_tcp2->connect_mode = p_conn->connect_mode;
		wval = p_conn->syn_ip_payload_length;
		p_tcp2->syn_ip_payload_length = cpu_to_le16(wval);
		p_tcp2->syn_phy_addr_lo = DMA_LO_LE(p_conn->syn_phy_addr);
		p_tcp2->syn_phy_addr_hi = DMA_HI_LE(p_conn->syn_phy_addr);
		p_tcp2->cwnd = cpu_to_le32(p_conn->cwnd);
		p_tcp2->ka_max_probe_cnt = p_conn->ka_probe_cnt;
		p_tcp2->ka_timeout = cpu_to_le32(p_conn->ka_timeout);
		p_tcp2->max_rt_time = cpu_to_le32(p_conn->max_rt_time);
		p_tcp2->ka_interval = cpu_to_le32(p_conn->ka_interval);
	}

	return qed_spq_post(p_hwfn, p_ent, NULL);
}