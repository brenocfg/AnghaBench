#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  tx_collisions; int /*<<< orphan*/  tx_late_collisions; int /*<<< orphan*/  tx_excessive_collisions; int /*<<< orphan*/  tx_deferred; int /*<<< orphan*/  tx_first_collisions; int /*<<< orphan*/  tx_underflows; int /*<<< orphan*/  tx_max_pkt_errs; int /*<<< orphan*/  rcvd_pkts_dropped; int /*<<< orphan*/  rx_overflows; int /*<<< orphan*/  rx_crc_errs; int /*<<< orphan*/  rx_other_errs; int /*<<< orphan*/  rx_length_errs; int /*<<< orphan*/  rx_align_errs; int /*<<< orphan*/  rx_code_violations; } ;
struct et131x_adapter {TYPE_3__ stats; TYPE_2__* regs; } ;
struct TYPE_4__ {int /*<<< orphan*/  carry_reg2; int /*<<< orphan*/  carry_reg1; } ;
struct TYPE_5__ {TYPE_1__ macstat; } ;

/* Variables and functions */
 scalar_t__ COUNTER_WRAP_12_BIT ; 
 scalar_t__ COUNTER_WRAP_16_BIT ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void et1310_handle_macstat_interrupt(struct et131x_adapter *adapter)
{
	u32 carry_reg1;
	u32 carry_reg2;

	/* Read the interrupt bits from the register(s).  These are Clear On
	 * Write.
	 */
	carry_reg1 = readl(&adapter->regs->macstat.carry_reg1);
	carry_reg2 = readl(&adapter->regs->macstat.carry_reg2);

	writel(carry_reg1, &adapter->regs->macstat.carry_reg1);
	writel(carry_reg2, &adapter->regs->macstat.carry_reg2);

	/* We need to do update the host copy of all the MAC_STAT counters.
	 * For each counter, check it's overflow bit.  If the overflow bit is
	 * set, then increment the host version of the count by one complete
	 * revolution of the counter.  This routine is called when the counter
	 * block indicates that one of the counters has wrapped.
	 */
	if (carry_reg1 & (1 << 14))
		adapter->stats.rx_code_violations	+= COUNTER_WRAP_16_BIT;
	if (carry_reg1 & (1 << 8))
		adapter->stats.rx_align_errs	+= COUNTER_WRAP_12_BIT;
	if (carry_reg1 & (1 << 7))
		adapter->stats.rx_length_errs	+= COUNTER_WRAP_16_BIT;
	if (carry_reg1 & (1 << 2))
		adapter->stats.rx_other_errs	+= COUNTER_WRAP_16_BIT;
	if (carry_reg1 & (1 << 6))
		adapter->stats.rx_crc_errs	+= COUNTER_WRAP_16_BIT;
	if (carry_reg1 & (1 << 3))
		adapter->stats.rx_overflows	+= COUNTER_WRAP_16_BIT;
	if (carry_reg1 & (1 << 0))
		adapter->stats.rcvd_pkts_dropped	+= COUNTER_WRAP_16_BIT;
	if (carry_reg2 & (1 << 16))
		adapter->stats.tx_max_pkt_errs	+= COUNTER_WRAP_12_BIT;
	if (carry_reg2 & (1 << 15))
		adapter->stats.tx_underflows	+= COUNTER_WRAP_12_BIT;
	if (carry_reg2 & (1 << 6))
		adapter->stats.tx_first_collisions += COUNTER_WRAP_12_BIT;
	if (carry_reg2 & (1 << 8))
		adapter->stats.tx_deferred	+= COUNTER_WRAP_12_BIT;
	if (carry_reg2 & (1 << 5))
		adapter->stats.tx_excessive_collisions += COUNTER_WRAP_12_BIT;
	if (carry_reg2 & (1 << 4))
		adapter->stats.tx_late_collisions	+= COUNTER_WRAP_12_BIT;
	if (carry_reg2 & (1 << 2))
		adapter->stats.tx_collisions	+= COUNTER_WRAP_12_BIT;
}