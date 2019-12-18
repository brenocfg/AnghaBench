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
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct rsp_que {TYPE_1__* qpair; struct req_que* req; } ;
struct req_que {int dummy; } ;
struct qla_hw_data {TYPE_1__* base_qpair; int /*<<< orphan*/  pdev; int /*<<< orphan*/  srb_mempool; int /*<<< orphan*/ * msix_entries; int /*<<< orphan*/  hardware_lock; } ;
struct TYPE_2__ {int use_shadow_reg; int /*<<< orphan*/  reqq_start_iocbs; int /*<<< orphan*/  pdev; int /*<<< orphan*/  enable_class_2; int /*<<< orphan*/  hints_list; int /*<<< orphan*/  srb_mempool; int /*<<< orphan*/ * msix; int /*<<< orphan*/ * qp_lock_ptr; struct scsi_qla_host* vha; struct rsp_que* rsp; struct req_que* req; struct qla_hw_data* hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA83XX (struct qla_hw_data*) ; 
 scalar_t__ IS_SHADOW_REG_CAPABLE (struct qla_hw_data*) ; 
 size_t QLA_MSIX_RSP_Q ; 
 int /*<<< orphan*/  ql2xenableclass2 ; 
 int /*<<< orphan*/  qla_83xx_start_iocbs ; 
 int /*<<< orphan*/  qla_cpu_update (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

__attribute__((used)) static void qla_init_base_qpair(struct scsi_qla_host *vha, struct req_que *req,
    struct rsp_que *rsp)
{
	struct qla_hw_data *ha = vha->hw;

	rsp->qpair = ha->base_qpair;
	rsp->req = req;
	ha->base_qpair->hw = ha;
	ha->base_qpair->req = req;
	ha->base_qpair->rsp = rsp;
	ha->base_qpair->vha = vha;
	ha->base_qpair->qp_lock_ptr = &ha->hardware_lock;
	ha->base_qpair->use_shadow_reg = IS_SHADOW_REG_CAPABLE(ha) ? 1 : 0;
	ha->base_qpair->msix = &ha->msix_entries[QLA_MSIX_RSP_Q];
	ha->base_qpair->srb_mempool = ha->srb_mempool;
	INIT_LIST_HEAD(&ha->base_qpair->hints_list);
	ha->base_qpair->enable_class_2 = ql2xenableclass2;
	/* init qpair to this cpu. Will adjust at run time. */
	qla_cpu_update(rsp->qpair, raw_smp_processor_id());
	ha->base_qpair->pdev = ha->pdev;

	if (IS_QLA27XX(ha) || IS_QLA83XX(ha) || IS_QLA28XX(ha))
		ha->base_qpair->reqq_start_iocbs = qla_83xx_start_iocbs;
}