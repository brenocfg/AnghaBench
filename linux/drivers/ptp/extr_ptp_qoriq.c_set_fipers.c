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
struct ptp_qoriq_registers {TYPE_1__* fiper_regs; } ;
struct ptp_qoriq {int /*<<< orphan*/  tmr_fiper2; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  tmr_fiper1; struct ptp_qoriq_registers regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_fiper2; int /*<<< orphan*/  tmr_fiper1; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_alarm (struct ptp_qoriq*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_fipers(struct ptp_qoriq *ptp_qoriq)
{
	struct ptp_qoriq_registers *regs = &ptp_qoriq->regs;

	set_alarm(ptp_qoriq);
	ptp_qoriq->write(&regs->fiper_regs->tmr_fiper1, ptp_qoriq->tmr_fiper1);
	ptp_qoriq->write(&regs->fiper_regs->tmr_fiper2, ptp_qoriq->tmr_fiper2);
}