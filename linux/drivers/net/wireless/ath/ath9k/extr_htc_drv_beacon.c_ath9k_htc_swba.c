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
struct wmi_event_swba {scalar_t__ beacon_pending; } ;
struct ath_common {int dummy; } ;
struct TYPE_2__ {scalar_t__ bmisscnt; int /*<<< orphan*/ ** bslot; } ;
struct ath9k_htc_priv {int /*<<< orphan*/  beacon_lock; TYPE_1__ beacon; int /*<<< orphan*/  fatal_work; int /*<<< orphan*/  hw; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSTUCK ; 
 scalar_t__ BSTUCK_THRESHOLD ; 
 int ath9k_htc_choose_bslot (struct ath9k_htc_priv*,struct wmi_event_swba*) ; 
 int /*<<< orphan*/  ath9k_htc_send_beacon (struct ath9k_htc_priv*,int) ; 
 int /*<<< orphan*/  ath9k_htc_send_buffered (struct ath9k_htc_priv*,int) ; 
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_dbg (struct ath_common*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void ath9k_htc_swba(struct ath9k_htc_priv *priv,
		    struct wmi_event_swba *swba)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	int slot;

	if (swba->beacon_pending != 0) {
		priv->beacon.bmisscnt++;
		if (priv->beacon.bmisscnt > BSTUCK_THRESHOLD) {
			ath_dbg(common, BSTUCK, "Beacon stuck, HW reset\n");
			ieee80211_queue_work(priv->hw,
					     &priv->fatal_work);
		}
		return;
	}

	if (priv->beacon.bmisscnt) {
		ath_dbg(common, BSTUCK,
			"Resuming beacon xmit after %u misses\n",
			priv->beacon.bmisscnt);
		priv->beacon.bmisscnt = 0;
	}

	slot = ath9k_htc_choose_bslot(priv, swba);
	spin_lock_bh(&priv->beacon_lock);
	if (priv->beacon.bslot[slot] == NULL) {
		spin_unlock_bh(&priv->beacon_lock);
		return;
	}
	spin_unlock_bh(&priv->beacon_lock);

	ath9k_htc_send_buffered(priv, slot);
	ath9k_htc_send_beacon(priv, slot);
}