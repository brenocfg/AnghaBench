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
struct petp {TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_PL_CAUSE ; 
 scalar_t__ A_TP_INT_CAUSE ; 
 int FPGA_PCIX_INTERRUPT_TP ; 
 scalar_t__ FPGA_TP_ADDR_INTERRUPT_CAUSE ; 
 int F_PL_INTR_TP ; 
 int /*<<< orphan*/  t1_is_asic (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void t1_tp_intr_clear(struct petp *tp)
{
#ifdef CONFIG_CHELSIO_T1_1G
	if (!t1_is_asic(tp->adapter)) {
		writel(0xffffffff,
		       tp->adapter->regs + FPGA_TP_ADDR_INTERRUPT_CAUSE);
		writel(FPGA_PCIX_INTERRUPT_TP, tp->adapter->regs + A_PL_CAUSE);
		return;
	}
#endif
	writel(0xffffffff, tp->adapter->regs + A_TP_INT_CAUSE);
	writel(F_PL_INTR_TP, tp->adapter->regs + A_PL_CAUSE);
}