#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct TYPE_12__ {int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_mid; int /*<<< orphan*/  addr_hi; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_mid; int /*<<< orphan*/  addr_hi; } ;
struct fcoe_conn_offload_ramrod_data {int /*<<< orphan*/  def_q_idx; int /*<<< orphan*/  flags; TYPE_5__ d_id; int /*<<< orphan*/  max_conc_seqs_c3; TYPE_3__ s_id; void* vlan_tag; void* rx_max_fc_pay_len; void* rec_rr_tov_timer_val; void* e_d_tov_timer_val; void* tx_max_fc_pay_len; void* src_mac_addr_hi; void* src_mac_addr_mid; void* src_mac_addr_lo; void* dst_mac_addr_hi; void* dst_mac_addr_mid; void* dst_mac_addr_lo; int /*<<< orphan*/  respq_next_page_addr; int /*<<< orphan*/  respq_curr_page_addr; int /*<<< orphan*/  respq_pbl_addr; int /*<<< orphan*/  xferq_next_page_addr; int /*<<< orphan*/  xferq_curr_page_addr; int /*<<< orphan*/  xferq_pbl_addr; int /*<<< orphan*/  sq_next_page_addr; int /*<<< orphan*/  sq_curr_page_addr; int /*<<< orphan*/  sq_pbl_addr; void* conn_id; void* physical_q0; } ;
struct fcoe_conn_offload_ramrod_params {struct fcoe_conn_offload_ramrod_data offload_ramrod_data; } ;
struct TYPE_9__ {struct fcoe_conn_offload_ramrod_params fcoe_conn_ofld; } ;
struct qed_spq_entry {TYPE_2__ ramrod; } ;
struct qed_spq_comp_cb {int dummy; } ;
struct qed_sp_init_data {int comp_mode; struct qed_spq_comp_cb* p_comp_data; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct TYPE_8__ {int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {TYPE_7__* cdev; TYPE_1__ hw_info; } ;
struct TYPE_13__ {int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_mid; int /*<<< orphan*/  addr_hi; } ;
struct TYPE_11__ {int /*<<< orphan*/  addr_lo; int /*<<< orphan*/  addr_mid; int /*<<< orphan*/  addr_hi; } ;
struct qed_fcoe_conn {void* conn_id; void* dst_mac_addr_lo; void* dst_mac_addr_mid; void* dst_mac_addr_hi; void* src_mac_addr_lo; void* src_mac_addr_mid; void* src_mac_addr_hi; void* tx_max_fc_pay_len; void* e_d_tov_timer_val; void* rec_tov_timer_val; void* rx_max_fc_pay_len; void* vlan_tag; int /*<<< orphan*/  def_q_idx; int /*<<< orphan*/  flags; TYPE_6__ d_id; int /*<<< orphan*/  max_conc_seqs_c3; TYPE_4__ s_id; int /*<<< orphan*/ * confq_addr; int /*<<< orphan*/  confq_pbl_addr; int /*<<< orphan*/ * xferq_addr; int /*<<< orphan*/  xferq_pbl_addr; int /*<<< orphan*/  sq_next_page_addr; int /*<<< orphan*/  sq_curr_page_addr; int /*<<< orphan*/  sq_pbl_addr; void* physical_q0; int /*<<< orphan*/  icid; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum spq_mode { ____Placeholder_spq_mode } spq_mode ;
struct TYPE_14__ {int /*<<< orphan*/  mf_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FCOE_CONN_OFFLOAD_RAMROD_DATA_B_SINGLE_VLAN ; 
 int /*<<< orphan*/  FCOE_RAMROD_CMD_ID_OFFLOAD_CONN ; 
 int /*<<< orphan*/  PQ_FLAGS_OFLD ; 
 int /*<<< orphan*/  PROTOCOLID_FCOE ; 
 int /*<<< orphan*/  QED_MF_UFP_SPECIFIC ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* cpu_to_le16 (void*) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 void* qed_get_cm_pq_idx (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
qed_sp_fcoe_conn_offload(struct qed_hwfn *p_hwfn,
			 struct qed_fcoe_conn *p_conn,
			 enum spq_mode comp_mode,
			 struct qed_spq_comp_cb *p_comp_addr)
{
	struct fcoe_conn_offload_ramrod_params *p_ramrod = NULL;
	struct fcoe_conn_offload_ramrod_data *p_data;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	u16 physical_q0, tmp;
	int rc;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_conn->icid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = comp_mode;
	init_data.p_comp_data = p_comp_addr;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 FCOE_RAMROD_CMD_ID_OFFLOAD_CONN,
				 PROTOCOLID_FCOE, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.fcoe_conn_ofld;
	p_data = &p_ramrod->offload_ramrod_data;

	/* Transmission PQ is the first of the PF */
	physical_q0 = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
	p_conn->physical_q0 = cpu_to_le16(physical_q0);
	p_data->physical_q0 = cpu_to_le16(physical_q0);

	p_data->conn_id = cpu_to_le16(p_conn->conn_id);
	DMA_REGPAIR_LE(p_data->sq_pbl_addr, p_conn->sq_pbl_addr);
	DMA_REGPAIR_LE(p_data->sq_curr_page_addr, p_conn->sq_curr_page_addr);
	DMA_REGPAIR_LE(p_data->sq_next_page_addr, p_conn->sq_next_page_addr);
	DMA_REGPAIR_LE(p_data->xferq_pbl_addr, p_conn->xferq_pbl_addr);
	DMA_REGPAIR_LE(p_data->xferq_curr_page_addr, p_conn->xferq_addr[0]);
	DMA_REGPAIR_LE(p_data->xferq_next_page_addr, p_conn->xferq_addr[1]);

	DMA_REGPAIR_LE(p_data->respq_pbl_addr, p_conn->confq_pbl_addr);
	DMA_REGPAIR_LE(p_data->respq_curr_page_addr, p_conn->confq_addr[0]);
	DMA_REGPAIR_LE(p_data->respq_next_page_addr, p_conn->confq_addr[1]);

	p_data->dst_mac_addr_lo = cpu_to_le16(p_conn->dst_mac_addr_lo);
	p_data->dst_mac_addr_mid = cpu_to_le16(p_conn->dst_mac_addr_mid);
	p_data->dst_mac_addr_hi = cpu_to_le16(p_conn->dst_mac_addr_hi);
	p_data->src_mac_addr_lo = cpu_to_le16(p_conn->src_mac_addr_lo);
	p_data->src_mac_addr_mid = cpu_to_le16(p_conn->src_mac_addr_mid);
	p_data->src_mac_addr_hi = cpu_to_le16(p_conn->src_mac_addr_hi);

	tmp = cpu_to_le16(p_conn->tx_max_fc_pay_len);
	p_data->tx_max_fc_pay_len = tmp;
	tmp = cpu_to_le16(p_conn->e_d_tov_timer_val);
	p_data->e_d_tov_timer_val = tmp;
	tmp = cpu_to_le16(p_conn->rec_tov_timer_val);
	p_data->rec_rr_tov_timer_val = tmp;
	tmp = cpu_to_le16(p_conn->rx_max_fc_pay_len);
	p_data->rx_max_fc_pay_len = tmp;

	p_data->vlan_tag = cpu_to_le16(p_conn->vlan_tag);
	p_data->s_id.addr_hi = p_conn->s_id.addr_hi;
	p_data->s_id.addr_mid = p_conn->s_id.addr_mid;
	p_data->s_id.addr_lo = p_conn->s_id.addr_lo;
	p_data->max_conc_seqs_c3 = p_conn->max_conc_seqs_c3;
	p_data->d_id.addr_hi = p_conn->d_id.addr_hi;
	p_data->d_id.addr_mid = p_conn->d_id.addr_mid;
	p_data->d_id.addr_lo = p_conn->d_id.addr_lo;
	p_data->flags = p_conn->flags;
	if (test_bit(QED_MF_UFP_SPECIFIC, &p_hwfn->cdev->mf_bits))
		SET_FIELD(p_data->flags,
			  FCOE_CONN_OFFLOAD_RAMROD_DATA_B_SINGLE_VLAN, 1);
	p_data->def_q_idx = p_conn->def_q_idx;

	return qed_spq_post(p_hwfn, p_ent, NULL);
}