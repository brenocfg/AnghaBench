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
struct rsp_que {int dummy; } ;
struct TYPE_8__ {int msi_enabled; int mr_intr_valid; } ;
struct qla_hw_data {int /*<<< orphan*/  hardware_lock; TYPE_2__ flags; TYPE_5__* pdev; TYPE_1__* isp_ops; int /*<<< orphan*/  fw_attributes; int /*<<< orphan*/  chip_revision; TYPE_4__* iobase; } ;
typedef  int /*<<< orphan*/  scsi_qla_host_t ;
struct TYPE_9__ {int /*<<< orphan*/  semaphore; } ;
struct TYPE_10__ {TYPE_3__ isp; } ;
typedef  TYPE_4__ device_reg_t ;
struct TYPE_11__ {int subsystem_device; int irq; int /*<<< orphan*/  revision; int /*<<< orphan*/  subsystem_vendor; } ;
struct TYPE_7__ {int /*<<< orphan*/  intr_handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  IS_CNA_CAPABLE (struct qla_hw_data*) ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_P3P_TYPE (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA2031 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA2432 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA24XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA2532 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA27XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA28XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA8001 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLA82XX (struct qla_hw_data*) ; 
 int /*<<< orphan*/  IS_QLA8432 (struct qla_hw_data*) ; 
 scalar_t__ IS_QLAFX00 (struct qla_hw_data*) ; 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  PCI_VENDOR_ID_HP ; 
 int /*<<< orphan*/  QLA2XXX_DRIVER_NAME ; 
 int QLA_FUNCTION_FAILED ; 
 int /*<<< orphan*/  QLA_MSIX_CHIP_REV_24XX ; 
 int /*<<< orphan*/  WRT_REG_WORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pci_alloc_irq_vectors (TYPE_5__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pci_get_drvdata (TYPE_5__*) ; 
 int ql2xenablemsix ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,...) ; 
 int /*<<< orphan*/  ql_dbg_init ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*,int,...) ; 
 int /*<<< orphan*/  ql_log_info ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int qla24xx_enable_msix (struct qla_hw_data*,struct rsp_que*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rsp_que*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
qla2x00_request_irqs(struct qla_hw_data *ha, struct rsp_que *rsp)
{
	int ret = QLA_FUNCTION_FAILED;
	device_reg_t *reg = ha->iobase;
	scsi_qla_host_t *vha = pci_get_drvdata(ha->pdev);

	/* If possible, enable MSI-X. */
	if (ql2xenablemsix == 0 || (!IS_QLA2432(ha) && !IS_QLA2532(ha) &&
	    !IS_QLA8432(ha) && !IS_CNA_CAPABLE(ha) && !IS_QLA2031(ha) &&
	    !IS_QLAFX00(ha) && !IS_QLA27XX(ha) && !IS_QLA28XX(ha)))
		goto skip_msi;

	if (ql2xenablemsix == 2)
		goto skip_msix;

	if (ha->pdev->subsystem_vendor == PCI_VENDOR_ID_HP &&
		(ha->pdev->subsystem_device == 0x7040 ||
		ha->pdev->subsystem_device == 0x7041 ||
		ha->pdev->subsystem_device == 0x1705)) {
		ql_log(ql_log_warn, vha, 0x0034,
		    "MSI-X: Unsupported ISP 2432 SSVID/SSDID (0x%X,0x%X).\n",
			ha->pdev->subsystem_vendor,
			ha->pdev->subsystem_device);
		goto skip_msi;
	}

	if (IS_QLA2432(ha) && (ha->pdev->revision < QLA_MSIX_CHIP_REV_24XX)) {
		ql_log(ql_log_warn, vha, 0x0035,
		    "MSI-X; Unsupported ISP2432 (0x%X, 0x%X).\n",
		    ha->pdev->revision, QLA_MSIX_CHIP_REV_24XX);
		goto skip_msix;
	}

	ret = qla24xx_enable_msix(ha, rsp);
	if (!ret) {
		ql_dbg(ql_dbg_init, vha, 0x0036,
		    "MSI-X: Enabled (0x%X, 0x%X).\n",
		    ha->chip_revision, ha->fw_attributes);
		goto clear_risc_ints;
	}

skip_msix:

	ql_log(ql_log_info, vha, 0x0037,
	    "Falling back-to MSI mode -%d.\n", ret);

	if (!IS_QLA24XX(ha) && !IS_QLA2532(ha) && !IS_QLA8432(ha) &&
	    !IS_QLA8001(ha) && !IS_P3P_TYPE(ha) && !IS_QLAFX00(ha) &&
	    !IS_QLA27XX(ha) && !IS_QLA28XX(ha))
		goto skip_msi;

	ret = pci_alloc_irq_vectors(ha->pdev, 1, 1, PCI_IRQ_MSI);
	if (!ret) {
		ql_dbg(ql_dbg_init, vha, 0x0038,
		    "MSI: Enabled.\n");
		ha->flags.msi_enabled = 1;
	} else
		ql_log(ql_log_warn, vha, 0x0039,
		    "Falling back-to INTa mode -- %d.\n", ret);
skip_msi:

	/* Skip INTx on ISP82xx. */
	if (!ha->flags.msi_enabled && IS_QLA82XX(ha))
		return QLA_FUNCTION_FAILED;

	ret = request_irq(ha->pdev->irq, ha->isp_ops->intr_handler,
	    ha->flags.msi_enabled ? 0 : IRQF_SHARED,
	    QLA2XXX_DRIVER_NAME, rsp);
	if (ret) {
		ql_log(ql_log_warn, vha, 0x003a,
		    "Failed to reserve interrupt %d already in use.\n",
		    ha->pdev->irq);
		goto fail;
	} else if (!ha->flags.msi_enabled) {
		ql_dbg(ql_dbg_init, vha, 0x0125,
		    "INTa mode: Enabled.\n");
		ha->flags.mr_intr_valid = 1;
	}

clear_risc_ints:
	if (IS_FWI2_CAPABLE(ha) || IS_QLAFX00(ha))
		goto fail;

	spin_lock_irq(&ha->hardware_lock);
	WRT_REG_WORD(&reg->isp.semaphore, 0);
	spin_unlock_irq(&ha->hardware_lock);

fail:
	return ret;
}