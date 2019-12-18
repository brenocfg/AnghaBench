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
struct ath10k_vif {int /*<<< orphan*/  vdev_id; int /*<<< orphan*/  tx_paused; struct ath10k* ar; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;
struct ath10k {int /*<<< orphan*/  hw; TYPE_1__ htt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int BITS_PER_LONG ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ath10k_mac_vif_tx_lock(struct ath10k_vif *arvif, int reason)
{
	struct ath10k *ar = arvif->ar;

	lockdep_assert_held(&ar->htt.tx_lock);

	WARN_ON(reason >= BITS_PER_LONG);
	arvif->tx_paused |= BIT(reason);
	ieee80211_stop_queue(ar->hw, arvif->vdev_id);
}