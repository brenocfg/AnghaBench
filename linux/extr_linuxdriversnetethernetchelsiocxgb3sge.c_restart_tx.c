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
struct sge_qset {TYPE_1__* txq; int /*<<< orphan*/  txq_stopped; int /*<<< orphan*/  tx_q; int /*<<< orphan*/  netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  qresume_tsk; int /*<<< orphan*/  restarts; } ;

/* Variables and functions */
 size_t TXQ_CTRL ; 
 size_t TXQ_ETH ; 
 size_t TXQ_OFLD ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (int /*<<< orphan*/ ) ; 
 scalar_t__ should_restart_tx (TYPE_1__*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void restart_tx(struct sge_qset *qs)
{
	if (test_bit(TXQ_ETH, &qs->txq_stopped) &&
	    should_restart_tx(&qs->txq[TXQ_ETH]) &&
	    test_and_clear_bit(TXQ_ETH, &qs->txq_stopped)) {
		qs->txq[TXQ_ETH].restarts++;
		if (netif_running(qs->netdev))
			netif_tx_wake_queue(qs->tx_q);
	}

	if (test_bit(TXQ_OFLD, &qs->txq_stopped) &&
	    should_restart_tx(&qs->txq[TXQ_OFLD]) &&
	    test_and_clear_bit(TXQ_OFLD, &qs->txq_stopped)) {
		qs->txq[TXQ_OFLD].restarts++;
		tasklet_schedule(&qs->txq[TXQ_OFLD].qresume_tsk);
	}
	if (test_bit(TXQ_CTRL, &qs->txq_stopped) &&
	    should_restart_tx(&qs->txq[TXQ_CTRL]) &&
	    test_and_clear_bit(TXQ_CTRL, &qs->txq_stopped)) {
		qs->txq[TXQ_CTRL].restarts++;
		tasklet_schedule(&qs->txq[TXQ_CTRL].qresume_tsk);
	}
}