#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hw {struct brcms_info* priv; } ;
struct brcms_info {int /*<<< orphan*/  lock; TYPE_3__* wlc; } ;
struct TYPE_6__ {TYPE_2__* vif; } ;
struct TYPE_4__ {int /*<<< orphan*/  dtim_period; } ;
struct TYPE_5__ {TYPE_1__ bss_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  brcms_c_set_new_beacon (TYPE_3__*,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* ieee80211_beacon_get_tim (struct ieee80211_hw*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int brcms_ops_beacon_set_tim(struct ieee80211_hw *hw,
				 struct ieee80211_sta *sta, bool set)
{
	struct brcms_info *wl = hw->priv;
	struct sk_buff *beacon = NULL;
	u16 tim_offset = 0;

	spin_lock_bh(&wl->lock);
	if (wl->wlc->vif)
		beacon = ieee80211_beacon_get_tim(hw, wl->wlc->vif,
						  &tim_offset, NULL);
	if (beacon)
		brcms_c_set_new_beacon(wl->wlc, beacon, tim_offset,
				       wl->wlc->vif->bss_conf.dtim_period);
	spin_unlock_bh(&wl->lock);

	return 0;
}