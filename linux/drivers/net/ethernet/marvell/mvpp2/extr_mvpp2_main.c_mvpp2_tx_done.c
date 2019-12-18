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
struct mvpp2_txq_pcpu {scalar_t__ count; } ;
struct mvpp2_tx_queue {int log_id; int /*<<< orphan*/  pcpu; } ;
struct mvpp2_port {int dummy; } ;

/* Variables and functions */
 struct mvpp2_tx_queue* mvpp2_get_tx_queue (struct mvpp2_port*,int) ; 
 int /*<<< orphan*/  mvpp2_txq_done (struct mvpp2_port*,struct mvpp2_tx_queue*,struct mvpp2_txq_pcpu*) ; 
 struct mvpp2_txq_pcpu* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int mvpp2_tx_done(struct mvpp2_port *port, u32 cause,
				  unsigned int thread)
{
	struct mvpp2_tx_queue *txq;
	struct mvpp2_txq_pcpu *txq_pcpu;
	unsigned int tx_todo = 0;

	while (cause) {
		txq = mvpp2_get_tx_queue(port, cause);
		if (!txq)
			break;

		txq_pcpu = per_cpu_ptr(txq->pcpu, thread);

		if (txq_pcpu->count) {
			mvpp2_txq_done(port, txq, txq_pcpu);
			tx_todo += txq_pcpu->count;
		}

		cause &= ~(1 << txq->log_id);
	}
	return tx_todo;
}