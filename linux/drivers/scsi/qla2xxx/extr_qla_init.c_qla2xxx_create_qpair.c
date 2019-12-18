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
typedef  size_t uint16_t ;
struct TYPE_5__ {int qpairs_available; } ;
struct scsi_qla_host {TYPE_1__ flags; int /*<<< orphan*/  qp_list; struct qla_hw_data* hw; } ;
struct qla_qpair {int use_shadow_reg; size_t id; int vp_idx; int difdix_supported; int online; int /*<<< orphan*/  qp_list_elem; struct qla_msix_entry* msix; TYPE_4__* rsp; int /*<<< orphan*/  srb_mempool; int /*<<< orphan*/  req; int /*<<< orphan*/  reqq_start_iocbs; int /*<<< orphan*/  pdev; int /*<<< orphan*/  enable_explicit_conf; int /*<<< orphan*/  enable_class_2; int /*<<< orphan*/  chip_reset; int /*<<< orphan*/  hints_list; int /*<<< orphan*/  fw_started; int /*<<< orphan*/  qp_lock; int /*<<< orphan*/ * qp_lock_ptr; struct scsi_qla_host* vha; struct qla_hw_data* hw; } ;
struct qla_msix_entry {int in_use; size_t vector; } ;
struct TYPE_6__ {int /*<<< orphan*/  fw_started; int /*<<< orphan*/  msix_enabled; } ;
struct qla_hw_data {int fw_attributes; scalar_t__ max_qpairs; scalar_t__ num_qpairs; int msix_count; int /*<<< orphan*/  mq_lock; int /*<<< orphan*/  qpair_qid_map; struct qla_qpair** queue_pair_map; int /*<<< orphan*/ * req_q_map; TYPE_4__** rsp_q_map; int /*<<< orphan*/  pdev; struct qla_msix_entry* msix_entries; TYPE_3__* base_qpair; TYPE_2__ flags; } ;
struct TYPE_8__ {struct qla_qpair* qpair; int /*<<< orphan*/  req; } ;
struct TYPE_7__ {int /*<<< orphan*/  enable_explicit_conf; int /*<<< orphan*/  enable_class_2; int /*<<< orphan*/  chip_reset; } ;

/* Variables and functions */
 int BIT_4 ; 
 int BIT_6 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 scalar_t__ IS_SHADOW_REG_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_T10_PI_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  SRB_MIN_REQ ; 
 int /*<<< orphan*/  clear_bit (size_t,int /*<<< orphan*/ ) ; 
 size_t find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct qla_qpair*) ; 
 struct qla_qpair* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ql2xenabledif ; 
 scalar_t__ ql2xmqsupport ; 
 scalar_t__ ql2xnvmeenable ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,size_t) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_dbg_multiq ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla25xx_create_req_que (struct qla_hw_data*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int) ; 
 int qla25xx_create_rsp_que (struct qla_hw_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct qla_qpair*,int) ; 
 int /*<<< orphan*/  qla25xx_delete_rsp_que (struct scsi_qla_host*,TYPE_4__*) ; 
 int /*<<< orphan*/  qla_83xx_start_iocbs ; 
 int /*<<< orphan*/  qla_cpu_update (struct qla_qpair*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srb_cachep ; 

struct qla_qpair *qla2xxx_create_qpair(struct scsi_qla_host *vha, int qos,
	int vp_idx, bool startqp)
{
	int rsp_id = 0;
	int  req_id = 0;
	int i;
	struct qla_hw_data *ha = vha->hw;
	uint16_t qpair_id = 0;
	struct qla_qpair *qpair = NULL;
	struct qla_msix_entry *msix;

	if (!(ha->fw_attributes & BIT_6) || !ha->flags.msix_enabled) {
		ql_log(ql_log_warn, vha, 0x00181,
		    "FW/Driver is not multi-queue capable.\n");
		return NULL;
	}

	if (ql2xmqsupport || ql2xnvmeenable) {
		qpair = kzalloc(sizeof(struct qla_qpair), GFP_KERNEL);
		if (qpair == NULL) {
			ql_log(ql_log_warn, vha, 0x0182,
			    "Failed to allocate memory for queue pair.\n");
			return NULL;
		}

		qpair->hw = vha->hw;
		qpair->vha = vha;
		qpair->qp_lock_ptr = &qpair->qp_lock;
		spin_lock_init(&qpair->qp_lock);
		qpair->use_shadow_reg = IS_SHADOW_REG_CAPABLE(ha) ? 1 : 0;

		/* Assign available que pair id */
		mutex_lock(&ha->mq_lock);
		qpair_id = find_first_zero_bit(ha->qpair_qid_map, ha->max_qpairs);
		if (ha->num_qpairs >= ha->max_qpairs) {
			mutex_unlock(&ha->mq_lock);
			ql_log(ql_log_warn, vha, 0x0183,
			    "No resources to create additional q pair.\n");
			goto fail_qid_map;
		}
		ha->num_qpairs++;
		set_bit(qpair_id, ha->qpair_qid_map);
		ha->queue_pair_map[qpair_id] = qpair;
		qpair->id = qpair_id;
		qpair->vp_idx = vp_idx;
		qpair->fw_started = ha->flags.fw_started;
		INIT_LIST_HEAD(&qpair->hints_list);
		qpair->chip_reset = ha->base_qpair->chip_reset;
		qpair->enable_class_2 = ha->base_qpair->enable_class_2;
		qpair->enable_explicit_conf =
		    ha->base_qpair->enable_explicit_conf;

		for (i = 0; i < ha->msix_count; i++) {
			msix = &ha->msix_entries[i];
			if (msix->in_use)
				continue;
			qpair->msix = msix;
			ql_dbg(ql_dbg_multiq, vha, 0xc00f,
			    "Vector %x selected for qpair\n", msix->vector);
			break;
		}
		if (!qpair->msix) {
			ql_log(ql_log_warn, vha, 0x0184,
			    "Out of MSI-X vectors!.\n");
			goto fail_msix;
		}

		qpair->msix->in_use = 1;
		list_add_tail(&qpair->qp_list_elem, &vha->qp_list);
		qpair->pdev = ha->pdev;
		if (IS_QLA27XX(ha) || IS_QLA83XX(ha) || IS_QLA28XX(ha))
			qpair->reqq_start_iocbs = qla_83xx_start_iocbs;

		mutex_unlock(&ha->mq_lock);

		/* Create response queue first */
		rsp_id = qla25xx_create_rsp_que(ha, 0, 0, 0, qpair, startqp);
		if (!rsp_id) {
			ql_log(ql_log_warn, vha, 0x0185,
			    "Failed to create response queue.\n");
			goto fail_rsp;
		}

		qpair->rsp = ha->rsp_q_map[rsp_id];

		/* Create request queue */
		req_id = qla25xx_create_req_que(ha, 0, vp_idx, 0, rsp_id, qos,
		    startqp);
		if (!req_id) {
			ql_log(ql_log_warn, vha, 0x0186,
			    "Failed to create request queue.\n");
			goto fail_req;
		}

		qpair->req = ha->req_q_map[req_id];
		qpair->rsp->req = qpair->req;
		qpair->rsp->qpair = qpair;
		/* init qpair to this cpu. Will adjust at run time. */
		qla_cpu_update(qpair, smp_processor_id());

		if (IS_T10_PI_CAPABLE(ha) && ql2xenabledif) {
			if (ha->fw_attributes & BIT_4)
				qpair->difdix_supported = 1;
		}

		qpair->srb_mempool = mempool_create_slab_pool(SRB_MIN_REQ, srb_cachep);
		if (!qpair->srb_mempool) {
			ql_log(ql_log_warn, vha, 0xd036,
			    "Failed to create srb mempool for qpair %d\n",
			    qpair->id);
			goto fail_mempool;
		}

		/* Mark as online */
		qpair->online = 1;

		if (!vha->flags.qpairs_available)
			vha->flags.qpairs_available = 1;

		ql_dbg(ql_dbg_multiq, vha, 0xc00d,
		    "Request/Response queue pair created, id %d\n",
		    qpair->id);
		ql_dbg(ql_dbg_init, vha, 0x0187,
		    "Request/Response queue pair created, id %d\n",
		    qpair->id);
	}
	return qpair;

fail_mempool:
fail_req:
	qla25xx_delete_rsp_que(vha, qpair->rsp);
fail_rsp:
	mutex_lock(&ha->mq_lock);
	qpair->msix->in_use = 0;
	list_del(&qpair->qp_list_elem);
	if (list_empty(&vha->qp_list))
		vha->flags.qpairs_available = 0;
fail_msix:
	ha->queue_pair_map[qpair_id] = NULL;
	clear_bit(qpair_id, ha->qpair_qid_map);
	ha->num_qpairs--;
	mutex_unlock(&ha->mq_lock);
fail_qid_map:
	kfree(qpair);
	return NULL;
}