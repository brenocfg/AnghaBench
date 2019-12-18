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
struct ptp_qoriq {int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int) ;struct ptp_qoriq_registers regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  tmr_cnt_h; int /*<<< orphan*/  tmr_cnt_l; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tmr_cnt_write(struct ptp_qoriq *ptp_qoriq, u64 ns)
{
	struct ptp_qoriq_registers *regs = &ptp_qoriq->regs;
	u32 hi = ns >> 32;
	u32 lo = ns & 0xffffffff;

	ptp_qoriq->write(&regs->ctrl_regs->tmr_cnt_l, lo);
	ptp_qoriq->write(&regs->ctrl_regs->tmr_cnt_h, hi);
}