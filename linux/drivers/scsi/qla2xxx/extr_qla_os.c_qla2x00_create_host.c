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
struct TYPE_5__ {int size; int /*<<< orphan*/  scan_work; int /*<<< orphan*/  l; } ;
struct TYPE_4__ {int size; int /*<<< orphan*/ * l; int /*<<< orphan*/  ldma; int /*<<< orphan*/  fcports; } ;
struct scsi_qla_host {struct qla_hw_data* hw; struct Scsi_Host* host; int /*<<< orphan*/  host_str; int /*<<< orphan*/  host_no; TYPE_2__ scan; TYPE_1__ gnl; int /*<<< orphan*/  vref_waitq; int /*<<< orphan*/  fcport_waitQ; int /*<<< orphan*/  cmd_list_lock; int /*<<< orphan*/  work_lock; int /*<<< orphan*/  iocb_work; int /*<<< orphan*/  gpnid_list; int /*<<< orphan*/  qp_list; int /*<<< orphan*/  plogi_ack_list; int /*<<< orphan*/  logo_list; int /*<<< orphan*/  qla_sess_op_cmd_list; int /*<<< orphan*/  qla_cmd_list; int /*<<< orphan*/  list; int /*<<< orphan*/  work_list; int /*<<< orphan*/  vp_fcports; int /*<<< orphan*/  ql2xiniexchg; int /*<<< orphan*/  ql2xexchoffld; int /*<<< orphan*/  qlini_mode; } ;
struct scsi_host_template {int dummy; } ;
struct qla_hw_data {int max_loop_id; int max_fibre_devices; TYPE_3__* pdev; } ;
struct get_name_list_extended {int dummy; } ;
struct fab_scan_rp {int dummy; } ;
struct Scsi_Host {int /*<<< orphan*/  host_no; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* QLA2XXX_DRIVER_NAME ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ql2x_ini_mode ; 
 int /*<<< orphan*/  ql2xexchoffld ; 
 int /*<<< orphan*/  ql2xiniexchg ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,struct Scsi_Host*,struct qla_hw_data*,struct scsi_qla_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*) ; 
 int /*<<< orphan*/  ql_log_fatal ; 
 int /*<<< orphan*/  ql_log_pci (int /*<<< orphan*/ ,TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  qla2x00_iocb_work_fn ; 
 int /*<<< orphan*/  qla_scan_work_fn ; 
 struct Scsi_Host* scsi_host_alloc (struct scsi_host_template*,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 struct scsi_qla_host* shost_priv (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc (int) ; 

struct scsi_qla_host *qla2x00_create_host(struct scsi_host_template *sht,
						struct qla_hw_data *ha)
{
	struct Scsi_Host *host;
	struct scsi_qla_host *vha = NULL;

	host = scsi_host_alloc(sht, sizeof(scsi_qla_host_t));
	if (!host) {
		ql_log_pci(ql_log_fatal, ha->pdev, 0x0107,
		    "Failed to allocate host from the scsi layer, aborting.\n");
		return NULL;
	}

	/* Clear our data area */
	vha = shost_priv(host);
	memset(vha, 0, sizeof(scsi_qla_host_t));

	vha->host = host;
	vha->host_no = host->host_no;
	vha->hw = ha;

	vha->qlini_mode = ql2x_ini_mode;
	vha->ql2xexchoffld = ql2xexchoffld;
	vha->ql2xiniexchg = ql2xiniexchg;

	INIT_LIST_HEAD(&vha->vp_fcports);
	INIT_LIST_HEAD(&vha->work_list);
	INIT_LIST_HEAD(&vha->list);
	INIT_LIST_HEAD(&vha->qla_cmd_list);
	INIT_LIST_HEAD(&vha->qla_sess_op_cmd_list);
	INIT_LIST_HEAD(&vha->logo_list);
	INIT_LIST_HEAD(&vha->plogi_ack_list);
	INIT_LIST_HEAD(&vha->qp_list);
	INIT_LIST_HEAD(&vha->gnl.fcports);
	INIT_LIST_HEAD(&vha->gpnid_list);
	INIT_WORK(&vha->iocb_work, qla2x00_iocb_work_fn);

	spin_lock_init(&vha->work_lock);
	spin_lock_init(&vha->cmd_list_lock);
	init_waitqueue_head(&vha->fcport_waitQ);
	init_waitqueue_head(&vha->vref_waitq);

	vha->gnl.size = sizeof(struct get_name_list_extended) *
			(ha->max_loop_id + 1);
	vha->gnl.l = dma_alloc_coherent(&ha->pdev->dev,
	    vha->gnl.size, &vha->gnl.ldma, GFP_KERNEL);
	if (!vha->gnl.l) {
		ql_log(ql_log_fatal, vha, 0xd04a,
		    "Alloc failed for name list.\n");
		scsi_host_put(vha->host);
		return NULL;
	}

	/* todo: what about ext login? */
	vha->scan.size = ha->max_fibre_devices * sizeof(struct fab_scan_rp);
	vha->scan.l = vmalloc(vha->scan.size);
	if (!vha->scan.l) {
		ql_log(ql_log_fatal, vha, 0xd04a,
		    "Alloc failed for scan database.\n");
		dma_free_coherent(&ha->pdev->dev, vha->gnl.size,
		    vha->gnl.l, vha->gnl.ldma);
		vha->gnl.l = NULL;
		scsi_host_put(vha->host);
		return NULL;
	}
	INIT_DELAYED_WORK(&vha->scan.scan_work, qla_scan_work_fn);

	sprintf(vha->host_str, "%s_%ld", QLA2XXX_DRIVER_NAME, vha->host_no);
	ql_dbg(ql_dbg_init, vha, 0x0041,
	    "Allocated the host=%p hw=%p vha=%p dev_name=%s",
	    vha->host, vha->hw, vha,
	    dev_name(&(ha->pdev->dev)));

	return vha;
}