#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct mvpp2_port {int /*<<< orphan*/  id; int /*<<< orphan*/  priv; scalar_t__ has_tx_irqs; } ;

/* Variables and functions */
 int MVPP2_CAUSE_MISC_SUM_MASK ; 
 int MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK ; 
 int MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_MASK ; 
 int /*<<< orphan*/  MVPP2_ISR_RX_TX_MASK_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_percpu_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static void mvpp2_interrupts_unmask(void *arg)
{
	struct mvpp2_port *port = arg;
	u32 val;

	val = MVPP2_CAUSE_MISC_SUM_MASK |
		MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK;
	if (port->has_tx_irqs)
		val |= MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_MASK;

	mvpp2_percpu_write(port->priv, smp_processor_id(),
			   MVPP2_ISR_RX_TX_MASK_REG(port->id), val);
}