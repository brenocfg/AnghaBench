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
struct mvpp2_txq_pcpu {int reserved_num; scalar_t__ count; } ;
struct mvpp2_tx_queue {int size; int /*<<< orphan*/  pcpu; } ;
struct mvpp2_port {TYPE_1__* priv; } ;
struct TYPE_2__ {unsigned int nthreads; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MVPP2_CPU_DESC_CHUNK ; 
 int MVPP2_MAX_THREADS ; 
 int max (int,int) ; 
 scalar_t__ mvpp2_txq_alloc_reserved_desc (struct mvpp2_port*,struct mvpp2_tx_queue*,int) ; 
 struct mvpp2_txq_pcpu* per_cpu_ptr (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int mvpp2_txq_reserved_desc_num_proc(struct mvpp2_port *port,
					    struct mvpp2_tx_queue *txq,
					    struct mvpp2_txq_pcpu *txq_pcpu,
					    int num)
{
	int req, desc_count;
	unsigned int thread;

	if (txq_pcpu->reserved_num >= num)
		return 0;

	/* Not enough descriptors reserved! Update the reserved descriptor
	 * count and check again.
	 */

	desc_count = 0;
	/* Compute total of used descriptors */
	for (thread = 0; thread < port->priv->nthreads; thread++) {
		struct mvpp2_txq_pcpu *txq_pcpu_aux;

		txq_pcpu_aux = per_cpu_ptr(txq->pcpu, thread);
		desc_count += txq_pcpu_aux->count;
		desc_count += txq_pcpu_aux->reserved_num;
	}

	req = max(MVPP2_CPU_DESC_CHUNK, num - txq_pcpu->reserved_num);
	desc_count += req;

	if (desc_count >
	   (txq->size - (MVPP2_MAX_THREADS * MVPP2_CPU_DESC_CHUNK)))
		return -ENOMEM;

	txq_pcpu->reserved_num += mvpp2_txq_alloc_reserved_desc(port, txq, req);

	/* OK, the descriptor could have been updated: check again. */
	if (txq_pcpu->reserved_num < num)
		return -ENOMEM;
	return 0;
}