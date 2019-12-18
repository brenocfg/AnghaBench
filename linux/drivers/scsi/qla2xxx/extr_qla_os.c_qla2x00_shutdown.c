#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ fw_started; scalar_t__ fce_enabled; } ;
struct qla_hw_data {TYPE_3__* isp_ops; scalar_t__ interrupts_on; TYPE_1__ flags; scalar_t__ eft; int /*<<< orphan*/  board_disable; } ;
struct pci_dev {int /*<<< orphan*/  enable_cnt; } ;
struct TYPE_15__ {scalar_t__ init_done; scalar_t__ online; } ;
struct TYPE_17__ {TYPE_2__ flags; scalar_t__ timer_active; int /*<<< orphan*/  pci_flags; struct qla_hw_data* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_16__ {int /*<<< orphan*/  (* disable_intrs ) (struct qla_hw_data*) ;} ;

/* Variables and functions */
 scalar_t__ IS_QLA2031 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA25XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA27XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA28XX (struct qla_hw_data*) ; 
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  PFLG_DRIVER_REMOVING ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 TYPE_4__* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  qla2x00_abort_isp_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  qla2x00_disable_eft_trace (TYPE_4__*) ; 
 int /*<<< orphan*/  qla2x00_disable_fce_trace (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qla2x00_free_fw_dump (struct qla_hw_data*) ; 
 int /*<<< orphan*/  qla2x00_free_irqs (TYPE_4__*) ; 
 int /*<<< orphan*/  qla2x00_stop_timer (TYPE_4__*) ; 
 int /*<<< orphan*/  qla2x00_try_to_stop_firmware (TYPE_4__*) ; 
 int /*<<< orphan*/  qlafx00_driver_shutdown (TYPE_4__*,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct qla_hw_data*) ; 

__attribute__((used)) static void
qla2x00_shutdown(struct pci_dev *pdev)
{
	scsi_qla_host_t *vha;
	struct qla_hw_data  *ha;

	vha = pci_get_drvdata(pdev);
	ha = vha->hw;

	ql_log(ql_log_info, vha, 0xfffa,
		"Adapter shutdown\n");

	/*
	 * Prevent future board_disable and wait
	 * until any pending board_disable has completed.
	 */
	set_bit(PFLG_DRIVER_REMOVING, &vha->pci_flags);
	cancel_work_sync(&ha->board_disable);

	if (!atomic_read(&pdev->enable_cnt))
		return;

	/* Notify ISPFX00 firmware */
	if (IS_QLAFX00(ha))
		qlafx00_driver_shutdown(vha, 20);

	/* Turn-off FCE trace */
	if (ha->flags.fce_enabled) {
		qla2x00_disable_fce_trace(vha, NULL, NULL);
		ha->flags.fce_enabled = 0;
	}

	/* Turn-off EFT trace */
	if (ha->eft)
		qla2x00_disable_eft_trace(vha);

	if (IS_QLA25XX(ha) ||  IS_QLA2031(ha) || IS_QLA27XX(ha) ||
	    IS_QLA28XX(ha)) {
		if (ha->flags.fw_started)
			qla2x00_abort_isp_cleanup(vha);
	} else {
		/* Stop currently executing firmware. */
		qla2x00_try_to_stop_firmware(vha);
	}

	/* Disable timer */
	if (vha->timer_active)
		qla2x00_stop_timer(vha);

	/* Turn adapter off line */
	vha->flags.online = 0;

	/* turn-off interrupts on the card */
	if (ha->interrupts_on) {
		vha->flags.init_done = 0;
		ha->isp_ops->disable_intrs(ha);
	}

	qla2x00_free_irqs(vha);

	qla2x00_free_fw_dump(ha);

	pci_disable_device(pdev);
	ql_log(ql_log_info, vha, 0xfffe,
		"Adapter shutdown successfully.\n");
}