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
struct netdev_queue {int dummy; } ;
struct mvneta_tx_queue {scalar_t__ count; scalar_t__ tx_wake_threshold; int /*<<< orphan*/  id; } ;
struct mvneta_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvneta_txq_bufs_free (struct mvneta_port*,struct mvneta_tx_queue*,int,struct netdev_queue*) ; 
 int mvneta_txq_sent_desc_proc (struct mvneta_port*,struct mvneta_tx_queue*) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 

__attribute__((used)) static void mvneta_txq_done(struct mvneta_port *pp,
			   struct mvneta_tx_queue *txq)
{
	struct netdev_queue *nq = netdev_get_tx_queue(pp->dev, txq->id);
	int tx_done;

	tx_done = mvneta_txq_sent_desc_proc(pp, txq);
	if (!tx_done)
		return;

	mvneta_txq_bufs_free(pp, txq, tx_done, nq);

	txq->count -= tx_done;

	if (netif_tx_queue_stopped(nq)) {
		if (txq->count <= txq->tx_wake_threshold)
			netif_tx_wake_queue(nq);
	}
}