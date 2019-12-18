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
struct ptp_qoriq_registers {TYPE_1__* ctrl_regs; } ;
struct ptp_qoriq {int /*<<< orphan*/  irq; int /*<<< orphan*/  base; int /*<<< orphan*/  clock; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;struct ptp_qoriq_registers regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_ctrl; int /*<<< orphan*/  tmr_temask; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct ptp_qoriq*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptp_qoriq_remove_debugfs (struct ptp_qoriq*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void ptp_qoriq_free(struct ptp_qoriq *ptp_qoriq)
{
	struct ptp_qoriq_registers *regs = &ptp_qoriq->regs;

	ptp_qoriq->write(&regs->ctrl_regs->tmr_temask, 0);
	ptp_qoriq->write(&regs->ctrl_regs->tmr_ctrl,   0);

	ptp_qoriq_remove_debugfs(ptp_qoriq);
	ptp_clock_unregister(ptp_qoriq->clock);
	iounmap(ptp_qoriq->base);
	free_irq(ptp_qoriq->irq, ptp_qoriq);
}