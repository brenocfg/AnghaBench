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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct ptp_qoriq_registers {TYPE_1__* ctrl_regs; } ;
struct ptp_qoriq {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* read ) (int /*<<< orphan*/ *) ;struct ptp_qoriq_registers regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PP2L ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptp_qoriq_fiper2_lpbk_set(void *data, u64 val)
{
	struct ptp_qoriq *ptp_qoriq = data;
	struct ptp_qoriq_registers *regs = &ptp_qoriq->regs;
	u32 ctrl;

	ctrl = ptp_qoriq->read(&regs->ctrl_regs->tmr_ctrl);
	if (val == 0)
		ctrl &= ~PP2L;
	else
		ctrl |= PP2L;

	ptp_qoriq->write(&regs->ctrl_regs->tmr_ctrl, ctrl);
	return 0;
}