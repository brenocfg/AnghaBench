#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct qedf_ctx {TYPE_4__* lport; int /*<<< orphan*/  io_mempool; int /*<<< orphan*/  cdev; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/ * dpc_wq; int /*<<< orphan*/  cmd_mgr; int /*<<< orphan*/  ctlr; int /*<<< orphan*/  grcdump; int /*<<< orphan*/ * ll2_recv_wq; int /*<<< orphan*/  flags; int /*<<< orphan*/ * timer_work_queue; int /*<<< orphan*/ * link_update_wq; int /*<<< orphan*/  link_update; } ;
struct pci_dev {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  host; } ;
struct TYPE_10__ {TYPE_2__* common; int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ) ;TYPE_1__* ll2; } ;
struct TYPE_9__ {int (* update_drv_state ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* slowpath_stop ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_power_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  QEDF_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDF_LL2_STARTED ; 
 int QEDF_MODE_RECOVERY ; 
 int /*<<< orphan*/  QEDF_UNLOADING ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fc_exch_mgr_free (TYPE_4__*) ; 
 int /*<<< orphan*/  fc_fabric_logoff (TYPE_4__*) ; 
 int /*<<< orphan*/  fc_lport_destroy (TYPE_4__*) ; 
 int /*<<< orphan*/  fc_lport_free_stats (TYPE_4__*) ; 
 int /*<<< orphan*/  fc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcoe_ctlr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fcoe_ctlr_link_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_destroy (int /*<<< orphan*/ ) ; 
 struct qedf_ctx* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 TYPE_3__* qed_ops ; 
 int /*<<< orphan*/  qedf_cmd_mgr_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedf_dbg_host_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_destroy_sb (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_free_fcoe_pf_param (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_free_grc_dump_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedf_remove_sysfs_ctx_attr (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_sync_free_irqs (struct qedf_ctx*) ; 
 int qedf_wait_for_upload (struct qedf_ctx*) ; 
 int /*<<< orphan*/  qedf_wait_for_vport_destroy (struct qedf_ctx*) ; 
 int /*<<< orphan*/  scsi_host_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __qedf_remove(struct pci_dev *pdev, int mode)
{
	struct qedf_ctx *qedf;
	int rc;

	if (!pdev) {
		QEDF_ERR(NULL, "pdev is NULL.\n");
		return;
	}

	qedf = pci_get_drvdata(pdev);

	/*
	 * Prevent race where we're in board disable work and then try to
	 * rmmod the module.
	 */
	if (test_bit(QEDF_UNLOADING, &qedf->flags)) {
		QEDF_ERR(&qedf->dbg_ctx, "Already removing PCI function.\n");
		return;
	}

	if (mode != QEDF_MODE_RECOVERY)
		set_bit(QEDF_UNLOADING, &qedf->flags);

	/* Logoff the fabric to upload all connections */
	if (mode == QEDF_MODE_RECOVERY)
		fcoe_ctlr_link_down(&qedf->ctlr);
	else
		fc_fabric_logoff(qedf->lport);

	if (qedf_wait_for_upload(qedf) == false)
		QEDF_ERR(&qedf->dbg_ctx, "Could not upload all sessions.\n");

#ifdef CONFIG_DEBUG_FS
	qedf_dbg_host_exit(&(qedf->dbg_ctx));
#endif

	/* Stop any link update handling */
	cancel_delayed_work_sync(&qedf->link_update);
	destroy_workqueue(qedf->link_update_wq);
	qedf->link_update_wq = NULL;

	if (qedf->timer_work_queue)
		destroy_workqueue(qedf->timer_work_queue);

	/* Stop Light L2 */
	clear_bit(QEDF_LL2_STARTED, &qedf->flags);
	qed_ops->ll2->stop(qedf->cdev);
	if (qedf->ll2_recv_wq)
		destroy_workqueue(qedf->ll2_recv_wq);

	/* Stop fastpath */
	qedf_sync_free_irqs(qedf);
	qedf_destroy_sb(qedf);

	/*
	 * During recovery don't destroy OS constructs that represent the
	 * physical port.
	 */
	if (mode != QEDF_MODE_RECOVERY) {
		qedf_free_grc_dump_buf(&qedf->grcdump);
		qedf_remove_sysfs_ctx_attr(qedf);

		/* Remove all SCSI/libfc/libfcoe structures */
		fcoe_ctlr_destroy(&qedf->ctlr);
		fc_lport_destroy(qedf->lport);
		fc_remove_host(qedf->lport->host);
		scsi_remove_host(qedf->lport->host);
	}

	qedf_cmd_mgr_free(qedf->cmd_mgr);

	if (mode != QEDF_MODE_RECOVERY) {
		fc_exch_mgr_free(qedf->lport);
		fc_lport_free_stats(qedf->lport);

		/* Wait for all vports to be reaped */
		qedf_wait_for_vport_destroy(qedf);
	}

	/*
	 * Now that all connections have been uploaded we can stop the
	 * rest of the qed operations
	 */
	qed_ops->stop(qedf->cdev);

	if (mode != QEDF_MODE_RECOVERY) {
		if (qedf->dpc_wq) {
			/* Stop general DPC handling */
			destroy_workqueue(qedf->dpc_wq);
			qedf->dpc_wq = NULL;
		}
	}

	/* Final shutdown for the board */
	qedf_free_fcoe_pf_param(qedf);
	if (mode != QEDF_MODE_RECOVERY) {
		qed_ops->common->set_power_state(qedf->cdev, PCI_D0);
		pci_set_drvdata(pdev, NULL);
	}

	rc = qed_ops->common->update_drv_state(qedf->cdev, false);
	if (rc)
		QEDF_ERR(&(qedf->dbg_ctx),
			"Failed to send drv state to MFW.\n");

	qed_ops->common->slowpath_stop(qedf->cdev);
	qed_ops->common->remove(qedf->cdev);

	mempool_destroy(qedf->io_mempool);

	/* Only reap the Scsi_host on a real removal */
	if (mode != QEDF_MODE_RECOVERY)
		scsi_host_put(qedf->lport->host);
}