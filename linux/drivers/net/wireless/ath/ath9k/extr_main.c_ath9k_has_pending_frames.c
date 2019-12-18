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
struct ath_txq {size_t mac80211_qnum; int /*<<< orphan*/  axq_lock; scalar_t__ axq_depth; } ;
struct ath_softc {TYPE_1__* cur_chan; } ;
struct ath_acq {int /*<<< orphan*/  acq_old; int /*<<< orphan*/  acq_new; } ;
struct TYPE_2__ {struct ath_acq* acq; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool ath9k_has_pending_frames(struct ath_softc *sc, struct ath_txq *txq,
				     bool sw_pending)
{
	bool pending = false;

	spin_lock_bh(&txq->axq_lock);

	if (txq->axq_depth) {
		pending = true;
		goto out;
	}

	if (!sw_pending)
		goto out;

	if (txq->mac80211_qnum >= 0) {
		struct ath_acq *acq;

		acq = &sc->cur_chan->acq[txq->mac80211_qnum];
		if (!list_empty(&acq->acq_new) || !list_empty(&acq->acq_old))
			pending = true;
	}
out:
	spin_unlock_bh(&txq->axq_lock);
	return pending;
}