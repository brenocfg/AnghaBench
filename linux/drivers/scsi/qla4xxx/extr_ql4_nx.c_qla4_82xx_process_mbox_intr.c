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
struct TYPE_7__ {int /*<<< orphan*/  tgt_mask_reg; } ;
struct scsi_qla_host {int mbox_status_count; TYPE_3__ nx_legacy_intr; TYPE_2__* pdev; int /*<<< orphan*/  flags; TYPE_1__* isp_ops; TYPE_4__* qla4_82xx_reg; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_status; int /*<<< orphan*/  host_int; } ;
struct TYPE_6__ {int /*<<< orphan*/  msix_enabled; int /*<<< orphan*/  msi_enabled; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* interrupt_service_routine ) (struct scsi_qla_host*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INTERRUPTS_ON ; 
 int ISRX_82XX_RISC_INT ; 
 int /*<<< orphan*/  qla4_82xx_wr_32 (struct scsi_qla_host*,int /*<<< orphan*/ ,int) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qla4_82xx_process_mbox_intr(struct scsi_qla_host *ha, int out_count)
{
	int intr_status;

	intr_status = readl(&ha->qla4_82xx_reg->host_int);
	if (intr_status & ISRX_82XX_RISC_INT) {
		ha->mbox_status_count = out_count;
		intr_status = readl(&ha->qla4_82xx_reg->host_status);
		ha->isp_ops->interrupt_service_routine(ha, intr_status);

		if (test_bit(AF_INTERRUPTS_ON, &ha->flags) &&
		    (!ha->pdev->msi_enabled && !ha->pdev->msix_enabled))
			qla4_82xx_wr_32(ha, ha->nx_legacy_intr.tgt_mask_reg,
					0xfbff);
	}
}