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
struct mvneta_tx_queue {int count; scalar_t__ txq_get_index; scalar_t__ txq_put_index; int /*<<< orphan*/  id; } ;
struct mvneta_port {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mvneta_txq_bufs_free (struct mvneta_port*,struct mvneta_tx_queue*,int,struct netdev_queue*) ; 
 struct netdev_queue* netdev_get_tx_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mvneta_txq_done_force(struct mvneta_port *pp,
				  struct mvneta_tx_queue *txq)

{
	struct netdev_queue *nq = netdev_get_tx_queue(pp->dev, txq->id);
	int tx_done = txq->count;

	mvneta_txq_bufs_free(pp, txq, tx_done, nq);

	/* reset txq */
	txq->count = 0;
	txq->txq_put_index = 0;
	txq->txq_get_index = 0;
}