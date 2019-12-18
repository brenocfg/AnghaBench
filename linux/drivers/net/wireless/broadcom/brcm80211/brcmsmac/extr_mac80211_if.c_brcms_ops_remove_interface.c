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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct brcms_info* priv; } ;
struct brcms_info {int /*<<< orphan*/  lock; TYPE_1__* wlc; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
brcms_ops_remove_interface(struct ieee80211_hw *hw, struct ieee80211_vif *vif)
{
	struct brcms_info *wl = hw->priv;

	spin_lock_bh(&wl->lock);
	wl->wlc->vif = NULL;
	spin_unlock_bh(&wl->lock);
}