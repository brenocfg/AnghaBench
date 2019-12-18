#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {struct nvmefc_fcp_req* desc; } ;
struct TYPE_12__ {TYPE_2__ nvme; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct scsi_qla_host {int dummy; } ;
struct qla_qpair {int /*<<< orphan*/  fw_started; } ;
struct qla_nvme_rport {TYPE_5__* fcport; } ;
struct nvmefc_fcp_req {struct nvme_private* private; } ;
struct nvme_private {TYPE_4__* sp; int /*<<< orphan*/  cmd_lock; } ;
struct nvme_fc_remote_port {struct qla_nvme_rport* private; } ;
struct nvme_fc_local_port {int dummy; } ;
struct TYPE_10__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_13__ {char* name; struct qla_qpair* qpair; int /*<<< orphan*/ * priv; int /*<<< orphan*/  nvme_ls_waitq; TYPE_1__ u; struct scsi_qla_host* vha; int /*<<< orphan*/  put_fn; int /*<<< orphan*/  done; int /*<<< orphan*/  type; int /*<<< orphan*/  cmd_kref; } ;
typedef  TYPE_4__ srb_t ;
struct TYPE_14__ {int nvme_flag; struct scsi_qla_host* vha; scalar_t__ deleted; } ;
typedef  TYPE_5__ fc_port_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int NVME_FLAG_RESETTING ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_NVME_CMD ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla2x00_start_nvme_mq (TYPE_4__*) ; 
 TYPE_4__* qla2xxx_get_qpair_sp (struct scsi_qla_host*,struct qla_qpair*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2xxx_rel_qpair_sp (struct qla_qpair*,TYPE_4__*) ; 
 int /*<<< orphan*/  qla_nvme_release_fcp_cmd_kref ; 
 int /*<<< orphan*/  qla_nvme_sp_done ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla_nvme_post_cmd(struct nvme_fc_local_port *lport,
    struct nvme_fc_remote_port *rport, void *hw_queue_handle,
    struct nvmefc_fcp_req *fd)
{
	fc_port_t *fcport;
	struct srb_iocb *nvme;
	struct scsi_qla_host *vha;
	int rval = -ENODEV;
	srb_t *sp;
	struct qla_qpair *qpair = hw_queue_handle;
	struct nvme_private *priv = fd->private;
	struct qla_nvme_rport *qla_rport = rport->private;

	fcport = qla_rport->fcport;

	if (!qpair || !fcport || (qpair && !qpair->fw_started) ||
	    (fcport && fcport->deleted))
		return rval;

	vha = fcport->vha;
	/*
	 * If we know the dev is going away while the transport is still sending
	 * IO's return busy back to stall the IO Q.  This happens when the
	 * link goes away and fw hasn't notified us yet, but IO's are being
	 * returned. If the dev comes back quickly we won't exhaust the IO
	 * retry count at the core.
	 */
	if (fcport->nvme_flag & NVME_FLAG_RESETTING)
		return -EBUSY;

	/* Alloc SRB structure */
	sp = qla2xxx_get_qpair_sp(vha, qpair, fcport, GFP_ATOMIC);
	if (!sp)
		return -EBUSY;

	init_waitqueue_head(&sp->nvme_ls_waitq);
	kref_init(&sp->cmd_kref);
	spin_lock_init(&priv->cmd_lock);
	sp->priv = (void *)priv;
	priv->sp = sp;
	sp->type = SRB_NVME_CMD;
	sp->name = "nvme_cmd";
	sp->done = qla_nvme_sp_done;
	sp->put_fn = qla_nvme_release_fcp_cmd_kref;
	sp->qpair = qpair;
	sp->vha = vha;
	nvme = &sp->u.iocb_cmd;
	nvme->u.nvme.desc = fd;

	rval = qla2x00_start_nvme_mq(sp);
	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x212d,
		    "qla2x00_start_nvme_mq failed = %d\n", rval);
		wake_up(&sp->nvme_ls_waitq);
		sp->priv = NULL;
		priv->sp = NULL;
		qla2xxx_rel_qpair_sp(sp->qpair, sp);
	}

	return rval;
}