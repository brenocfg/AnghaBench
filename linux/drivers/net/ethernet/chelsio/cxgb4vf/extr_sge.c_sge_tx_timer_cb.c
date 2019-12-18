#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_5__ {int in_use; } ;
struct sge_eth_txq {int /*<<< orphan*/  txq; TYPE_2__ q; } ;
struct sge {unsigned int ethtxq_rover; unsigned int ethqsets; int /*<<< orphan*/  tx_timer; struct sge_eth_txq* ethtxq; } ;
struct adapter {struct sge sge; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_timer; } ;

/* Variables and functions */
 unsigned int MAX_TIMER_TX_RECLAIM ; 
 int TX_QCHECK_PERIOD ; 
 scalar_t__ __netif_tx_trylock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __netif_tx_unlock (int /*<<< orphan*/ ) ; 
 struct adapter* adapter ; 
 int /*<<< orphan*/  free_tx_desc (struct adapter*,TYPE_2__*,int,int) ; 
 struct adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int reclaimable (TYPE_2__*) ; 
 TYPE_1__ sge ; 

__attribute__((used)) static void sge_tx_timer_cb(struct timer_list *t)
{
	struct adapter *adapter = from_timer(adapter, t, sge.tx_timer);
	struct sge *s = &adapter->sge;
	unsigned int i, budget;

	budget = MAX_TIMER_TX_RECLAIM;
	i = s->ethtxq_rover;
	do {
		struct sge_eth_txq *txq = &s->ethtxq[i];

		if (reclaimable(&txq->q) && __netif_tx_trylock(txq->txq)) {
			int avail = reclaimable(&txq->q);

			if (avail > budget)
				avail = budget;

			free_tx_desc(adapter, &txq->q, avail, true);
			txq->q.in_use -= avail;
			__netif_tx_unlock(txq->txq);

			budget -= avail;
			if (!budget)
				break;
		}

		i++;
		if (i >= s->ethqsets)
			i = 0;
	} while (i != s->ethtxq_rover);
	s->ethtxq_rover = i;

	/*
	 * If we found too many reclaimable packets schedule a timer in the
	 * near future to continue where we left off.  Otherwise the next timer
	 * will be at its normal interval.
	 */
	mod_timer(&s->tx_timer, jiffies + (budget ? TX_QCHECK_PERIOD : 2));
}