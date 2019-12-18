#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  size_t u16 ;
struct ieee80211_txq {int dummy; } ;
struct ath10k_peer {TYPE_2__* vif; TYPE_1__* sta; scalar_t__ removed; } ;
struct ath10k {struct ath10k_peer** peer_map; int /*<<< orphan*/  data_lock; } ;
struct TYPE_4__ {struct ieee80211_txq* txq; } ;
struct TYPE_3__ {struct ieee80211_txq** txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

struct ieee80211_txq *ath10k_mac_txq_lookup(struct ath10k *ar,
					    u16 peer_id,
					    u8 tid)
{
	struct ath10k_peer *peer;

	lockdep_assert_held(&ar->data_lock);

	peer = ar->peer_map[peer_id];
	if (!peer)
		return NULL;

	if (peer->removed)
		return NULL;

	if (peer->sta)
		return peer->sta->txq[tid];
	else if (peer->vif)
		return peer->vif->txq;
	else
		return NULL;
}