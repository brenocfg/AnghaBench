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
struct ieee80211_hw {struct brcms_info* priv; } ;
struct brcms_info {TYPE_2__* pub; int /*<<< orphan*/  lock; int /*<<< orphan*/  wlc; } ;
struct TYPE_4__ {TYPE_1__* ieee_hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int brcms_c_check_radio_disabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void brcms_ops_rfkill_poll(struct ieee80211_hw *hw)
{
	struct brcms_info *wl = hw->priv;
	bool blocked;

	spin_lock_bh(&wl->lock);
	blocked = brcms_c_check_radio_disabled(wl->wlc);
	spin_unlock_bh(&wl->lock);

	wiphy_rfkill_set_hw_state(wl->pub->ieee_hw->wiphy, blocked);
}