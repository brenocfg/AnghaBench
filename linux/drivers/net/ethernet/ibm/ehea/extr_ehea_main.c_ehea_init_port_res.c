#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  void* u64 ;
struct port_res_cfg {int /*<<< orphan*/  max_entries_rq3; int /*<<< orphan*/  max_entries_rq2; int /*<<< orphan*/  max_entries_rq1; int /*<<< orphan*/  max_entries_sq; int /*<<< orphan*/  max_entries_scq; int /*<<< orphan*/  max_entries_rcq; } ;
struct ehea_qp_init_attr {int low_lat_rq1; int signalingtype; int rq_count; int qp_token; int act_nr_send_wqes; int act_nr_rwqes_rq1; int act_nr_rwqes_rq2; int act_nr_rwqes_rq3; int /*<<< orphan*/  qp_nr; int /*<<< orphan*/  aff_eq_handle; int /*<<< orphan*/  recv_cq_handle; int /*<<< orphan*/  send_cq_handle; int /*<<< orphan*/  port_nr; int /*<<< orphan*/  rq3_threshold; int /*<<< orphan*/  rq2_threshold; int /*<<< orphan*/  wqe_size_enc_rq3; int /*<<< orphan*/  wqe_size_enc_rq2; int /*<<< orphan*/  wqe_size_enc_rq1; int /*<<< orphan*/  wqe_size_enc_sq; int /*<<< orphan*/  max_nr_rwqes_rq3; int /*<<< orphan*/  max_nr_rwqes_rq2; int /*<<< orphan*/  max_nr_rwqes_rq1; int /*<<< orphan*/  max_nr_send_wqes; } ;
struct TYPE_9__ {int /*<<< orphan*/  arr; } ;
struct ehea_port_res {int sq_skba_size; int swqe_refill_th; TYPE_4__* eq; TYPE_5__* recv_cq; TYPE_5__* send_cq; int /*<<< orphan*/  qp; TYPE_3__ rq3_skba; TYPE_3__ rq2_skba; TYPE_3__ rq1_skba; TYPE_3__ sq_skba; int /*<<< orphan*/  napi; struct ehea_port* port; int /*<<< orphan*/  swqe_avail; void* rx_packets; void* rx_bytes; void* tx_packets; void* tx_bytes; } ;
struct ehea_port {int /*<<< orphan*/  netdev; TYPE_2__* qp_eq; int /*<<< orphan*/  logical_port_id; struct ehea_adapter* adapter; } ;
struct ehea_adapter {int /*<<< orphan*/  pd; } ;
typedef  enum ehea_eq_type { ____Placeholder_ehea_eq_type } ehea_eq_type ;
struct TYPE_7__ {int /*<<< orphan*/  act_nr_of_cqes; } ;
struct TYPE_11__ {int /*<<< orphan*/  fw_handle; TYPE_1__ attr; } ;
struct TYPE_10__ {int /*<<< orphan*/  fw_handle; } ;
struct TYPE_8__ {int /*<<< orphan*/  fw_handle; } ;

/* Variables and functions */
 int EHEA_EQ ; 
 int /*<<< orphan*/  EHEA_MAX_ENTRIES_EQ ; 
 int /*<<< orphan*/  EHEA_RQ2_THRESHOLD ; 
 int /*<<< orphan*/  EHEA_RQ3_THRESHOLD ; 
 int /*<<< orphan*/  EHEA_SG_RQ1 ; 
 int /*<<< orphan*/  EHEA_SG_RQ2 ; 
 int /*<<< orphan*/  EHEA_SG_RQ3 ; 
 int /*<<< orphan*/  EHEA_SG_SQ ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 void* ehea_create_cq (struct ehea_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* ehea_create_eq (struct ehea_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehea_create_qp (struct ehea_adapter*,int /*<<< orphan*/ ,struct ehea_qp_init_attr*) ; 
 int /*<<< orphan*/  ehea_destroy_cq (TYPE_5__*) ; 
 int /*<<< orphan*/  ehea_destroy_eq (TYPE_4__*) ; 
 int /*<<< orphan*/  ehea_destroy_qp (int /*<<< orphan*/ ) ; 
 scalar_t__ ehea_gen_smrs (struct ehea_port_res*) ; 
 int ehea_init_q_skba (TYPE_3__*,int) ; 
 int /*<<< orphan*/  ehea_poll ; 
 int /*<<< orphan*/  kfree (struct ehea_qp_init_attr*) ; 
 struct ehea_qp_init_attr* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ehea_port_res*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ netif_msg_ifup (struct ehea_port*) ; 
 int /*<<< orphan*/  netif_napi_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ehea_init_port_res(struct ehea_port *port, struct ehea_port_res *pr,
			      struct port_res_cfg *pr_cfg, int queue_token)
{
	struct ehea_adapter *adapter = port->adapter;
	enum ehea_eq_type eq_type = EHEA_EQ;
	struct ehea_qp_init_attr *init_attr = NULL;
	int ret = -EIO;
	u64 tx_bytes, rx_bytes, tx_packets, rx_packets;

	tx_bytes = pr->tx_bytes;
	tx_packets = pr->tx_packets;
	rx_bytes = pr->rx_bytes;
	rx_packets = pr->rx_packets;

	memset(pr, 0, sizeof(struct ehea_port_res));

	pr->tx_bytes = tx_bytes;
	pr->tx_packets = tx_packets;
	pr->rx_bytes = rx_bytes;
	pr->rx_packets = rx_packets;

	pr->port = port;

	pr->eq = ehea_create_eq(adapter, eq_type, EHEA_MAX_ENTRIES_EQ, 0);
	if (!pr->eq) {
		pr_err("create_eq failed (eq)\n");
		goto out_free;
	}

	pr->recv_cq = ehea_create_cq(adapter, pr_cfg->max_entries_rcq,
				     pr->eq->fw_handle,
				     port->logical_port_id);
	if (!pr->recv_cq) {
		pr_err("create_cq failed (cq_recv)\n");
		goto out_free;
	}

	pr->send_cq = ehea_create_cq(adapter, pr_cfg->max_entries_scq,
				     pr->eq->fw_handle,
				     port->logical_port_id);
	if (!pr->send_cq) {
		pr_err("create_cq failed (cq_send)\n");
		goto out_free;
	}

	if (netif_msg_ifup(port))
		pr_info("Send CQ: act_nr_cqes=%d, Recv CQ: act_nr_cqes=%d\n",
			pr->send_cq->attr.act_nr_of_cqes,
			pr->recv_cq->attr.act_nr_of_cqes);

	init_attr = kzalloc(sizeof(*init_attr), GFP_KERNEL);
	if (!init_attr) {
		ret = -ENOMEM;
		pr_err("no mem for ehea_qp_init_attr\n");
		goto out_free;
	}

	init_attr->low_lat_rq1 = 1;
	init_attr->signalingtype = 1;	/* generate CQE if specified in WQE */
	init_attr->rq_count = 3;
	init_attr->qp_token = queue_token;
	init_attr->max_nr_send_wqes = pr_cfg->max_entries_sq;
	init_attr->max_nr_rwqes_rq1 = pr_cfg->max_entries_rq1;
	init_attr->max_nr_rwqes_rq2 = pr_cfg->max_entries_rq2;
	init_attr->max_nr_rwqes_rq3 = pr_cfg->max_entries_rq3;
	init_attr->wqe_size_enc_sq = EHEA_SG_SQ;
	init_attr->wqe_size_enc_rq1 = EHEA_SG_RQ1;
	init_attr->wqe_size_enc_rq2 = EHEA_SG_RQ2;
	init_attr->wqe_size_enc_rq3 = EHEA_SG_RQ3;
	init_attr->rq2_threshold = EHEA_RQ2_THRESHOLD;
	init_attr->rq3_threshold = EHEA_RQ3_THRESHOLD;
	init_attr->port_nr = port->logical_port_id;
	init_attr->send_cq_handle = pr->send_cq->fw_handle;
	init_attr->recv_cq_handle = pr->recv_cq->fw_handle;
	init_attr->aff_eq_handle = port->qp_eq->fw_handle;

	pr->qp = ehea_create_qp(adapter, adapter->pd, init_attr);
	if (!pr->qp) {
		pr_err("create_qp failed\n");
		ret = -EIO;
		goto out_free;
	}

	if (netif_msg_ifup(port))
		pr_info("QP: qp_nr=%d\n act_nr_snd_wqe=%d\n nr_rwqe_rq1=%d\n nr_rwqe_rq2=%d\n nr_rwqe_rq3=%d\n",
			init_attr->qp_nr,
			init_attr->act_nr_send_wqes,
			init_attr->act_nr_rwqes_rq1,
			init_attr->act_nr_rwqes_rq2,
			init_attr->act_nr_rwqes_rq3);

	pr->sq_skba_size = init_attr->act_nr_send_wqes + 1;

	ret = ehea_init_q_skba(&pr->sq_skba, pr->sq_skba_size);
	ret |= ehea_init_q_skba(&pr->rq1_skba, init_attr->act_nr_rwqes_rq1 + 1);
	ret |= ehea_init_q_skba(&pr->rq2_skba, init_attr->act_nr_rwqes_rq2 + 1);
	ret |= ehea_init_q_skba(&pr->rq3_skba, init_attr->act_nr_rwqes_rq3 + 1);
	if (ret)
		goto out_free;

	pr->swqe_refill_th = init_attr->act_nr_send_wqes / 10;
	if (ehea_gen_smrs(pr) != 0) {
		ret = -EIO;
		goto out_free;
	}

	atomic_set(&pr->swqe_avail, init_attr->act_nr_send_wqes - 1);

	kfree(init_attr);

	netif_napi_add(pr->port->netdev, &pr->napi, ehea_poll, 64);

	ret = 0;
	goto out;

out_free:
	kfree(init_attr);
	vfree(pr->sq_skba.arr);
	vfree(pr->rq1_skba.arr);
	vfree(pr->rq2_skba.arr);
	vfree(pr->rq3_skba.arr);
	ehea_destroy_qp(pr->qp);
	ehea_destroy_cq(pr->send_cq);
	ehea_destroy_cq(pr->recv_cq);
	ehea_destroy_eq(pr->eq);
out:
	return ret;
}