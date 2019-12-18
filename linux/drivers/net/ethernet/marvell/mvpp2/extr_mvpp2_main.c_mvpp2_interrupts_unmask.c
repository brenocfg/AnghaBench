#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mvpp2_port {int /*<<< orphan*/  id; TYPE_1__* priv; scalar_t__ has_tx_irqs; } ;
struct TYPE_3__ {scalar_t__ nthreads; int /*<<< orphan*/  hw_version; } ;

/* Variables and functions */
 int MVPP2_CAUSE_MISC_SUM_MASK ; 
 int MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK (int /*<<< orphan*/ ) ; 
 int MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_MASK ; 
 int /*<<< orphan*/  MVPP2_ISR_RX_TX_MASK_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cpu_to_thread (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mvpp2_thread_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static void mvpp2_interrupts_unmask(void *arg)
{
	struct mvpp2_port *port = arg;
	u32 val;

	/* If the thread isn't used, don't do anything */
	if (smp_processor_id() > port->priv->nthreads)
		return;

	val = MVPP2_CAUSE_MISC_SUM_MASK |
		MVPP2_CAUSE_RXQ_OCCUP_DESC_ALL_MASK(port->priv->hw_version);
	if (port->has_tx_irqs)
		val |= MVPP2_CAUSE_TXQ_OCCUP_DESC_ALL_MASK;

	mvpp2_thread_write(port->priv,
			   mvpp2_cpu_to_thread(port->priv, smp_processor_id()),
			   MVPP2_ISR_RX_TX_MASK_REG(port->id), val);
}