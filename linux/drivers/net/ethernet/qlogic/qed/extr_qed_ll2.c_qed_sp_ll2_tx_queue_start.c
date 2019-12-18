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
struct core_tx_start_ramrod_data {int stats_en; int /*<<< orphan*/  gsi_offload_flag; void* conn_type; void* qm_pq_id; void* pbl_size; int /*<<< orphan*/  pbl_base_addr; int /*<<< orphan*/  stats_id; void* mtu; int /*<<< orphan*/  sb_index; void* sb_id; } ;
struct TYPE_4__ {struct core_tx_start_ramrod_data core_tx_queue_start; } ;
struct qed_spq_entry {TYPE_1__ ramrod; } ;
struct qed_sp_init_data {int /*<<< orphan*/  comp_mode; int /*<<< orphan*/  opaque_fid; int /*<<< orphan*/  cid; } ;
struct qed_ll2_tx_queue {int /*<<< orphan*/  db_msg; int /*<<< orphan*/  doorbell_addr; int /*<<< orphan*/  txq_chain; int /*<<< orphan*/  tx_sb_index; } ;
struct TYPE_6__ {int conn_type; int tx_tc; int /*<<< orphan*/  gsi_enable; int /*<<< orphan*/  mtu; } ;
struct qed_ll2_info {int tx_stats_en; TYPE_3__ input; int /*<<< orphan*/  tx_stats_id; int /*<<< orphan*/  cid; struct qed_ll2_tx_queue tx_queue; } ;
struct TYPE_5__ {int /*<<< orphan*/  personality; int /*<<< orphan*/  opaque_fid; } ;
struct qed_hwfn {int /*<<< orphan*/  cdev; TYPE_2__ hw_info; } ;
typedef  int /*<<< orphan*/  init_data ;
typedef  enum qed_ll2_conn_type { ____Placeholder_qed_ll2_conn_type } qed_ll2_conn_type ;

/* Variables and functions */
 int /*<<< orphan*/  CORE_RAMROD_TX_QUEUE_START ; 
 int /*<<< orphan*/  DB_REC_KERNEL ; 
 int /*<<< orphan*/  DB_REC_WIDTH_32B ; 
 int /*<<< orphan*/  DMA_REGPAIR_LE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*,int) ; 
 int EINVAL ; 
#define  PKT_LB_TC 134 
 int /*<<< orphan*/  PQ_FLAGS_LB ; 
 int /*<<< orphan*/  PQ_FLAGS_OFLD ; 
 int /*<<< orphan*/  PQ_FLAGS_OOO ; 
 int /*<<< orphan*/  PROTOCOLID_CORE ; 
 void* PROTOCOLID_ETH ; 
 void* PROTOCOLID_FCOE ; 
 void* PROTOCOLID_ISCSI ; 
 void* PROTOCOLID_IWARP ; 
 void* PROTOCOLID_ROCE ; 
#define  PURE_LB_TC 133 
 int /*<<< orphan*/  QED_LL2_TX_REGISTERED (struct qed_ll2_info*) ; 
#define  QED_LL2_TYPE_FCOE 132 
#define  QED_LL2_TYPE_ISCSI 131 
#define  QED_LL2_TYPE_IWARP 130 
#define  QED_LL2_TYPE_OOO 129 
#define  QED_LL2_TYPE_ROCE 128 
 int /*<<< orphan*/  QED_PCI_ISCSI ; 
 int /*<<< orphan*/  QED_SPQ_MODE_EBLOCK ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct qed_sp_init_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qed_chain_get_page_cnt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qed_chain_get_pbl_phys (int /*<<< orphan*/ *) ; 
 int qed_db_recovery_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_get_cm_pq_idx (struct qed_hwfn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qed_int_get_sp_sb_id (struct qed_hwfn*) ; 
 int qed_sp_init_request (struct qed_hwfn*,struct qed_spq_entry**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qed_sp_init_data*) ; 
 int qed_spq_post (struct qed_hwfn*,struct qed_spq_entry*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qed_sp_ll2_tx_queue_start(struct qed_hwfn *p_hwfn,
				     struct qed_ll2_info *p_ll2_conn)
{
	enum qed_ll2_conn_type conn_type = p_ll2_conn->input.conn_type;
	struct qed_ll2_tx_queue *p_tx = &p_ll2_conn->tx_queue;
	struct core_tx_start_ramrod_data *p_ramrod = NULL;
	struct qed_spq_entry *p_ent = NULL;
	struct qed_sp_init_data init_data;
	u16 pq_id = 0, pbl_size;
	int rc = -EINVAL;

	if (!QED_LL2_TX_REGISTERED(p_ll2_conn))
		return 0;

	if (p_ll2_conn->input.conn_type == QED_LL2_TYPE_OOO)
		p_ll2_conn->tx_stats_en = 0;
	else
		p_ll2_conn->tx_stats_en = 1;

	/* Get SPQ entry */
	memset(&init_data, 0, sizeof(init_data));
	init_data.cid = p_ll2_conn->cid;
	init_data.opaque_fid = p_hwfn->hw_info.opaque_fid;
	init_data.comp_mode = QED_SPQ_MODE_EBLOCK;

	rc = qed_sp_init_request(p_hwfn, &p_ent,
				 CORE_RAMROD_TX_QUEUE_START,
				 PROTOCOLID_CORE, &init_data);
	if (rc)
		return rc;

	p_ramrod = &p_ent->ramrod.core_tx_queue_start;

	p_ramrod->sb_id = cpu_to_le16(qed_int_get_sp_sb_id(p_hwfn));
	p_ramrod->sb_index = p_tx->tx_sb_index;
	p_ramrod->mtu = cpu_to_le16(p_ll2_conn->input.mtu);
	p_ramrod->stats_en = p_ll2_conn->tx_stats_en;
	p_ramrod->stats_id = p_ll2_conn->tx_stats_id;

	DMA_REGPAIR_LE(p_ramrod->pbl_base_addr,
		       qed_chain_get_pbl_phys(&p_tx->txq_chain));
	pbl_size = qed_chain_get_page_cnt(&p_tx->txq_chain);
	p_ramrod->pbl_size = cpu_to_le16(pbl_size);

	switch (p_ll2_conn->input.tx_tc) {
	case PURE_LB_TC:
		pq_id = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_LB);
		break;
	case PKT_LB_TC:
		pq_id = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OOO);
		break;
	default:
		pq_id = qed_get_cm_pq_idx(p_hwfn, PQ_FLAGS_OFLD);
		break;
	}

	p_ramrod->qm_pq_id = cpu_to_le16(pq_id);

	switch (conn_type) {
	case QED_LL2_TYPE_FCOE:
		p_ramrod->conn_type = PROTOCOLID_FCOE;
		break;
	case QED_LL2_TYPE_ISCSI:
		p_ramrod->conn_type = PROTOCOLID_ISCSI;
		break;
	case QED_LL2_TYPE_ROCE:
		p_ramrod->conn_type = PROTOCOLID_ROCE;
		break;
	case QED_LL2_TYPE_IWARP:
		p_ramrod->conn_type = PROTOCOLID_IWARP;
		break;
	case QED_LL2_TYPE_OOO:
		if (p_hwfn->hw_info.personality == QED_PCI_ISCSI)
			p_ramrod->conn_type = PROTOCOLID_ISCSI;
		else
			p_ramrod->conn_type = PROTOCOLID_IWARP;
		break;
	default:
		p_ramrod->conn_type = PROTOCOLID_ETH;
		DP_NOTICE(p_hwfn, "Unknown connection type: %d\n", conn_type);
	}

	p_ramrod->gsi_offload_flag = p_ll2_conn->input.gsi_enable;

	rc = qed_spq_post(p_hwfn, p_ent, NULL);
	if (rc)
		return rc;

	rc = qed_db_recovery_add(p_hwfn->cdev, p_tx->doorbell_addr,
				 &p_tx->db_msg, DB_REC_WIDTH_32B,
				 DB_REC_KERNEL);
	return rc;
}