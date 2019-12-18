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
typedef  int u64 ;
typedef  int u32 ;
struct ptp_qoriq_registers {TYPE_1__* ctrl_regs; } ;
struct ptp_qoriq {int (* read ) (int /*<<< orphan*/ *) ;struct ptp_qoriq_registers regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_ctrl; } ;

/* Variables and functions */
 int PP2L ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ptp_qoriq_fiper2_lpbk_get(void *data, u64 *val)
{
	struct ptp_qoriq *ptp_qoriq = data;
	struct ptp_qoriq_registers *regs = &ptp_qoriq->regs;
	u32 ctrl;

	ctrl = ptp_qoriq->read(&regs->ctrl_regs->tmr_ctrl);
	*val = ctrl & PP2L ? 1 : 0;

	return 0;
}