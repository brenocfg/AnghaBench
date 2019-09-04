#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct sge_uld_txq {int /*<<< orphan*/  qresume_tsk; } ;
struct TYPE_9__ {int in_use; } ;
struct sge_eth_txq {TYPE_5__* txq; TYPE_3__ q; } ;
struct sge {unsigned long* txq_maperr; unsigned int ethtxq_rover; unsigned int ethqsets; int /*<<< orphan*/  tx_timer; struct sge_eth_txq* ethtxq; struct sge_eth_txq ptptxq; struct sge_uld_txq** egr_map; int /*<<< orphan*/  egr_sz; } ;
struct TYPE_7__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  ptp_lock; TYPE_1__ params; struct sge sge; } ;
struct TYPE_10__ {scalar_t__ trans_start; } ;
struct TYPE_8__ {int /*<<< orphan*/  tx_timer; } ;

/* Variables and functions */
 unsigned int BITS_PER_LONG ; 
 unsigned int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int HZ ; 
 unsigned int MAX_TIMER_TX_RECLAIM ; 
 int TX_QCHECK_PERIOD ; 
 unsigned int __ffs (unsigned long) ; 
 scalar_t__ __netif_tx_trylock (TYPE_5__*) ; 
 int /*<<< orphan*/  __netif_tx_unlock (TYPE_5__*) ; 
 struct adapter* adap ; 
 int /*<<< orphan*/  clear_bit (unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  free_tx_desc (struct adapter*,TYPE_3__*,int,int) ; 
 struct adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_t4 (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int reclaimable (TYPE_3__*) ; 
 TYPE_2__ sge ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void sge_tx_timer_cb(struct timer_list *t)
{
	unsigned long m;
	unsigned int i, budget;
	struct adapter *adap = from_timer(adap, t, sge.tx_timer);
	struct sge *s = &adap->sge;

	for (i = 0; i < BITS_TO_LONGS(s->egr_sz); i++)
		for (m = s->txq_maperr[i]; m; m &= m - 1) {
			unsigned long id = __ffs(m) + i * BITS_PER_LONG;
			struct sge_uld_txq *txq = s->egr_map[id];

			clear_bit(id, s->txq_maperr);
			tasklet_schedule(&txq->qresume_tsk);
		}

	if (!is_t4(adap->params.chip)) {
		struct sge_eth_txq *q = &s->ptptxq;
		int avail;

		spin_lock(&adap->ptp_lock);
		avail = reclaimable(&q->q);

		if (avail) {
			free_tx_desc(adap, &q->q, avail, false);
			q->q.in_use -= avail;
		}
		spin_unlock(&adap->ptp_lock);
	}

	budget = MAX_TIMER_TX_RECLAIM;
	i = s->ethtxq_rover;
	do {
		struct sge_eth_txq *q = &s->ethtxq[i];

		if (q->q.in_use &&
		    time_after_eq(jiffies, q->txq->trans_start + HZ / 100) &&
		    __netif_tx_trylock(q->txq)) {
			int avail = reclaimable(&q->q);

			if (avail) {
				if (avail > budget)
					avail = budget;

				free_tx_desc(adap, &q->q, avail, true);
				q->q.in_use -= avail;
				budget -= avail;
			}
			__netif_tx_unlock(q->txq);
		}

		if (++i >= s->ethqsets)
			i = 0;
	} while (budget && i != s->ethtxq_rover);
	s->ethtxq_rover = i;
	mod_timer(&s->tx_timer, jiffies + (budget ? TX_QCHECK_PERIOD : 2));
}