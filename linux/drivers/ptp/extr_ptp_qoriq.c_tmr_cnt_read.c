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
struct TYPE_2__ {int /*<<< orphan*/  tmr_cnt_h; int /*<<< orphan*/  tmr_cnt_l; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *) ; 
 int stub2 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u64 tmr_cnt_read(struct ptp_qoriq *ptp_qoriq)
{
	struct ptp_qoriq_registers *regs = &ptp_qoriq->regs;
	u64 ns;
	u32 lo, hi;

	lo = ptp_qoriq->read(&regs->ctrl_regs->tmr_cnt_l);
	hi = ptp_qoriq->read(&regs->ctrl_regs->tmr_cnt_h);
	ns = ((u64) hi) << 32;
	ns |= lo;
	return ns;
}