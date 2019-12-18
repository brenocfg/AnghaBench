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
struct mvpp2_tx_queue {int /*<<< orphan*/  id; } ;
struct mvpp2_port {int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int MVPP2_TRANSMITTED_COUNT_MASK ; 
 int MVPP2_TRANSMITTED_COUNT_OFFSET ; 
 int /*<<< orphan*/  MVPP2_TXQ_SENT_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvpp2_cpu_to_thread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mvpp2_thread_read_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static inline int mvpp2_txq_sent_desc_proc(struct mvpp2_port *port,
					   struct mvpp2_tx_queue *txq)
{
	u32 val;

	/* Reading status reg resets transmitted descriptor counter */
	val = mvpp2_thread_read_relaxed(port->priv,
					mvpp2_cpu_to_thread(port->priv, smp_processor_id()),
					MVPP2_TXQ_SENT_REG(txq->id));

	return (val & MVPP2_TRANSMITTED_COUNT_MASK) >>
		MVPP2_TRANSMITTED_COUNT_OFFSET;
}