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
typedef  int /*<<< orphan*/  u32 ;
struct petp {TYPE_1__* adapter; } ;
struct TYPE_2__ {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ A_TP_INT_CAUSE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  t1_is_asic (TYPE_1__*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int t1_tp_intr_handler(struct petp *tp)
{
	u32 cause;

#ifdef CONFIG_CHELSIO_T1_1G
	/* FPGA doesn't support TP interrupts. */
	if (!t1_is_asic(tp->adapter))
		return 1;
#endif

	cause = readl(tp->adapter->regs + A_TP_INT_CAUSE);
	writel(cause, tp->adapter->regs + A_TP_INT_CAUSE);
	return 0;
}