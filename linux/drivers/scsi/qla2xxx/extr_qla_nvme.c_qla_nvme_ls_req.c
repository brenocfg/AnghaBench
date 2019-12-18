#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  cmd_dma; int /*<<< orphan*/  timeout_sec; int /*<<< orphan*/  rsp_dma; int /*<<< orphan*/  rsp_len; int /*<<< orphan*/  cmd_len; scalar_t__ dl; scalar_t__ dir; struct nvmefc_ls_req* desc; } ;
struct TYPE_16__ {TYPE_4__ nvme; } ;
struct srb_iocb {TYPE_5__ u; } ;
struct scsi_qla_host {struct qla_hw_data* hw; } ;
struct qla_nvme_rport {TYPE_7__* fcport; } ;
struct TYPE_12__ {int /*<<< orphan*/  fw_started; } ;
struct qla_hw_data {TYPE_3__* pdev; TYPE_1__ flags; } ;
struct nvmefc_ls_req {int /*<<< orphan*/  rqstlen; int /*<<< orphan*/  rqstaddr; int /*<<< orphan*/  timeout; int /*<<< orphan*/  rspdma; int /*<<< orphan*/  rsplen; struct nvme_private* private; } ;
struct nvme_private {TYPE_6__* sp; struct nvmefc_ls_req* fd; int /*<<< orphan*/  cmd_lock; } ;
struct nvme_fc_remote_port {struct qla_nvme_rport* private; } ;
struct nvme_fc_local_port {int dummy; } ;
struct TYPE_13__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_17__ {char* name; int /*<<< orphan*/ * priv; int /*<<< orphan*/  nvme_ls_waitq; TYPE_2__ u; int /*<<< orphan*/  cmd_kref; int /*<<< orphan*/  put_fn; int /*<<< orphan*/  done; int /*<<< orphan*/  type; } ;
typedef  TYPE_6__ srb_t ;
struct TYPE_18__ {struct scsi_qla_host* vha; scalar_t__ deleted; } ;
typedef  TYPE_7__ fc_port_t ;
struct TYPE_14__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  SRB_NVME_LS ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 TYPE_6__* qla2x00_get_sp (struct scsi_qla_host*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qla2x00_rel_sp (TYPE_6__*) ; 
 int qla2x00_start_sp (TYPE_6__*) ; 
 int /*<<< orphan*/  qla_nvme_release_ls_cmd_kref ; 
 int /*<<< orphan*/  qla_nvme_sp_ls_done ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla_nvme_ls_req(struct nvme_fc_local_port *lport,
    struct nvme_fc_remote_port *rport, struct nvmefc_ls_req *fd)
{
	struct qla_nvme_rport *qla_rport = rport->private;
	fc_port_t *fcport = qla_rport->fcport;
	struct srb_iocb   *nvme;
	struct nvme_private *priv = fd->private;
	struct scsi_qla_host *vha;
	int     rval = QLA_FUNCTION_FAILED;
	struct qla_hw_data *ha;
	srb_t           *sp;


	if (!fcport || (fcport && fcport->deleted))
		return rval;

	vha = fcport->vha;
	ha = vha->hw;

	if (!ha->flags.fw_started)
		return rval;

	/* Alloc SRB structure */
	sp = qla2x00_get_sp(vha, fcport, GFP_ATOMIC);
	if (!sp)
		return rval;

	sp->type = SRB_NVME_LS;
	sp->name = "nvme_ls";
	sp->done = qla_nvme_sp_ls_done;
	sp->put_fn = qla_nvme_release_ls_cmd_kref;
	sp->priv = (void *)priv;
	priv->sp = sp;
	kref_init(&sp->cmd_kref);
	spin_lock_init(&priv->cmd_lock);
	nvme = &sp->u.iocb_cmd;
	priv->fd = fd;
	nvme->u.nvme.desc = fd;
	nvme->u.nvme.dir = 0;
	nvme->u.nvme.dl = 0;
	nvme->u.nvme.cmd_len = fd->rqstlen;
	nvme->u.nvme.rsp_len = fd->rsplen;
	nvme->u.nvme.rsp_dma = fd->rspdma;
	nvme->u.nvme.timeout_sec = fd->timeout;
	nvme->u.nvme.cmd_dma = dma_map_single(&ha->pdev->dev, fd->rqstaddr,
	    fd->rqstlen, DMA_TO_DEVICE);
	dma_sync_single_for_device(&ha->pdev->dev, nvme->u.nvme.cmd_dma,
	    fd->rqstlen, DMA_TO_DEVICE);

	rval = qla2x00_start_sp(sp);
	if (rval != QLA_SUCCESS) {
		ql_log(ql_log_warn, vha, 0x700e,
		    "qla2x00_start_sp failed = %d\n", rval);
		wake_up(&sp->nvme_ls_waitq);
		sp->priv = NULL;
		priv->sp = NULL;
		qla2x00_rel_sp(sp);
		return rval;
	}

	return rval;
}