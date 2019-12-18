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
struct mvumi_hw_regs {unsigned int int_mu; unsigned int int_comaerr; unsigned int clic_out_err; unsigned int clic_in_err; unsigned int int_comaout; unsigned int clic_irq; unsigned int int_dl_cpu2pciea; int /*<<< orphan*/  arm_to_pciea_drbl_reg; int /*<<< orphan*/  outb_isr_cause; int /*<<< orphan*/  main_int_cause_reg; } ;
struct mvumi_hba {unsigned int global_isr; unsigned int isr_status; struct mvumi_hw_regs* regs; TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVICE_ID_MARVELL_MV9580 ; 
 unsigned int ioread32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (unsigned int) ; 

__attribute__((used)) static int mvumi_clear_intr(void *extend)
{
	struct mvumi_hba *mhba = (struct mvumi_hba *) extend;
	unsigned int status, isr_status = 0, tmp = 0;
	struct mvumi_hw_regs *regs = mhba->regs;

	status = ioread32(regs->main_int_cause_reg);
	if (!(status & regs->int_mu) || status == 0xFFFFFFFF)
		return 1;
	if (unlikely(status & regs->int_comaerr)) {
		tmp = ioread32(regs->outb_isr_cause);
		if (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580) {
			if (tmp & regs->clic_out_err) {
				iowrite32(tmp & regs->clic_out_err,
							regs->outb_isr_cause);
			}
		} else {
			if (tmp & (regs->clic_in_err | regs->clic_out_err))
				iowrite32(tmp & (regs->clic_in_err |
						regs->clic_out_err),
						regs->outb_isr_cause);
		}
		status ^= mhba->regs->int_comaerr;
		/* inbound or outbound parity error, command will timeout */
	}
	if (status & regs->int_comaout) {
		tmp = ioread32(regs->outb_isr_cause);
		if (tmp & regs->clic_irq)
			iowrite32(tmp & regs->clic_irq, regs->outb_isr_cause);
	}
	if (status & regs->int_dl_cpu2pciea) {
		isr_status = ioread32(regs->arm_to_pciea_drbl_reg);
		if (isr_status)
			iowrite32(isr_status, regs->arm_to_pciea_drbl_reg);
	}

	mhba->global_isr = status;
	mhba->isr_status = isr_status;

	return 0;
}