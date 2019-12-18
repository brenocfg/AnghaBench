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
struct netdev_queue {int dummy; } ;
struct mvneta_tx_queue {int id; scalar_t__ count; } ;
struct mvneta_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __netif_tx_lock (struct netdev_queue*,int) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 struct mvneta_tx_queue* mvneta_tx_done_policy (struct mvneta_port*,int) ; 
 int /*<<< orphan*/  mvneta_txq_done (struct mvneta_port*,struct mvneta_tx_queue*) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int) ; 
 int smp_processor_id () ; 

__attribute__((used)) static void mvneta_tx_done_gbe(struct mvneta_port *pp, u32 cause_tx_done)
{
	struct mvneta_tx_queue *txq;
	struct netdev_queue *nq;
	int cpu = smp_processor_id();

	while (cause_tx_done) {
		txq = mvneta_tx_done_policy(pp, cause_tx_done);

		nq = netdev_get_tx_queue(pp->dev, txq->id);
		__netif_tx_lock(nq, cpu);

		if (txq->count)
			mvneta_txq_done(pp, txq);

		__netif_tx_unlock(nq);
		cause_tx_done &= ~((1 << txq->id));
	}
}