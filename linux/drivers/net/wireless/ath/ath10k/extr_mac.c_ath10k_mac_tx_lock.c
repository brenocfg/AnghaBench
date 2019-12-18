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
struct TYPE_2__ {int /*<<< orphan*/  tx_lock; } ;
struct ath10k {int /*<<< orphan*/  hw; int /*<<< orphan*/  tx_paused; TYPE_1__ htt; } ;

/* Variables and functions */
 int ATH10K_TX_PAUSE_MAX ; 
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_stop_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ath10k_mac_tx_lock(struct ath10k *ar, int reason)
{
	lockdep_assert_held(&ar->htt.tx_lock);

	WARN_ON(reason >= ATH10K_TX_PAUSE_MAX);
	ar->tx_paused |= BIT(reason);
	ieee80211_stop_queues(ar->hw);
}