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
struct TYPE_2__ {int /*<<< orphan*/  stops; } ;
struct sge_eth_txq {TYPE_1__ q; int /*<<< orphan*/  txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void txq_stop(struct sge_eth_txq *txq)
{
	netif_tx_stop_queue(txq->txq);
	txq->q.stops++;
}