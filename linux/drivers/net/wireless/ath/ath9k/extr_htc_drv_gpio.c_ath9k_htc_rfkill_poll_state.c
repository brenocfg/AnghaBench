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
struct ieee80211_hw {int /*<<< orphan*/  wiphy; struct ath9k_htc_priv* priv; } ;
struct ath9k_htc_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath_is_rfkill_set (struct ath9k_htc_priv*) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

void ath9k_htc_rfkill_poll_state(struct ieee80211_hw *hw)
{
	struct ath9k_htc_priv *priv = hw->priv;
	bool blocked = !!ath_is_rfkill_set(priv);

	wiphy_rfkill_set_hw_state(hw->wiphy, blocked);
}