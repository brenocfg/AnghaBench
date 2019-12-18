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
struct qedi_ctx {scalar_t__ boot_kset; int /*<<< orphan*/ * ll2_recv_thread; int /*<<< orphan*/  shost; int /*<<< orphan*/  udev; int /*<<< orphan*/  cdev; int /*<<< orphan*/  flags; int /*<<< orphan*/  dbg_ctx; int /*<<< orphan*/ * offload_thread; int /*<<< orphan*/ * tmf_thread; } ;
struct pci_dev {int dummy; } ;
struct TYPE_6__ {TYPE_2__* common; TYPE_1__* ll2; int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {int (* update_drv_state ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* remove ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* slowpath_stop ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_power_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* stop ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  QEDI_ERR (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  QEDI_IN_OFFLINE ; 
 int QEDI_MODE_NORMAL ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iscsi_boot_destroy_kset (scalar_t__) ; 
 int /*<<< orphan*/  iscsi_host_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 struct qedi_ctx* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  qedi_cm_free_mem (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_dbg_host_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qedi_destroy_fp (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_free_iscsi_pf_param (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_free_itt (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_free_uio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedi_ll2_free_skbs (struct qedi_ctx*) ; 
 TYPE_3__* qedi_ops ; 
 int /*<<< orphan*/  qedi_release_cid_que (struct qedi_ctx*) ; 
 int /*<<< orphan*/  qedi_sync_free_irqs (struct qedi_ctx*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int stub4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __qedi_remove(struct pci_dev *pdev, int mode)
{
	struct qedi_ctx *qedi = pci_get_drvdata(pdev);
	int rval;

	if (qedi->tmf_thread) {
		flush_workqueue(qedi->tmf_thread);
		destroy_workqueue(qedi->tmf_thread);
		qedi->tmf_thread = NULL;
	}

	if (qedi->offload_thread) {
		flush_workqueue(qedi->offload_thread);
		destroy_workqueue(qedi->offload_thread);
		qedi->offload_thread = NULL;
	}

#ifdef CONFIG_DEBUG_FS
	qedi_dbg_host_exit(&qedi->dbg_ctx);
#endif
	if (!test_bit(QEDI_IN_OFFLINE, &qedi->flags))
		qedi_ops->common->set_power_state(qedi->cdev, PCI_D0);

	qedi_sync_free_irqs(qedi);

	if (!test_bit(QEDI_IN_OFFLINE, &qedi->flags)) {
		qedi_ops->stop(qedi->cdev);
		qedi_ops->ll2->stop(qedi->cdev);
	}

	if (mode == QEDI_MODE_NORMAL)
		qedi_free_iscsi_pf_param(qedi);

	rval = qedi_ops->common->update_drv_state(qedi->cdev, false);
	if (rval)
		QEDI_ERR(&qedi->dbg_ctx, "Failed to send drv state to MFW\n");

	if (!test_bit(QEDI_IN_OFFLINE, &qedi->flags)) {
		qedi_ops->common->slowpath_stop(qedi->cdev);
		qedi_ops->common->remove(qedi->cdev);
	}

	qedi_destroy_fp(qedi);

	if (mode == QEDI_MODE_NORMAL) {
		qedi_release_cid_que(qedi);
		qedi_cm_free_mem(qedi);
		qedi_free_uio(qedi->udev);
		qedi_free_itt(qedi);

		iscsi_host_remove(qedi->shost);
		iscsi_host_free(qedi->shost);

		if (qedi->ll2_recv_thread) {
			kthread_stop(qedi->ll2_recv_thread);
			qedi->ll2_recv_thread = NULL;
		}
		qedi_ll2_free_skbs(qedi);

		if (qedi->boot_kset)
			iscsi_boot_destroy_kset(qedi->boot_kset);
	}
}