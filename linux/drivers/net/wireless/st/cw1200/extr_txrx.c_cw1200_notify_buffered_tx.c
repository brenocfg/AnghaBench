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
typedef  scalar_t__ u8 ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_sta {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr1; } ;
struct cw1200_common {int /*<<< orphan*/  vif; int /*<<< orphan*/  ps_state_lock; TYPE_1__* link_id_db; } ;
struct TYPE_2__ {scalar_t__* buffered; } ;

/* Variables and functions */
 int CW1200_MAX_TID ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ieee80211_sta* ieee80211_find_sta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_sta_set_buffered (struct ieee80211_sta*,int,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cw1200_notify_buffered_tx(struct cw1200_common *priv,
			       struct sk_buff *skb, int link_id, int tid)
{
	struct ieee80211_sta *sta;
	struct ieee80211_hdr *hdr;
	u8 *buffered;
	u8 still_buffered = 0;

	if (link_id && tid < CW1200_MAX_TID) {
		buffered = priv->link_id_db
				[link_id - 1].buffered;

		spin_lock_bh(&priv->ps_state_lock);
		if (!WARN_ON(!buffered[tid]))
			still_buffered = --buffered[tid];
		spin_unlock_bh(&priv->ps_state_lock);

		if (!still_buffered && tid < CW1200_MAX_TID) {
			hdr = (struct ieee80211_hdr *)skb->data;
			rcu_read_lock();
			sta = ieee80211_find_sta(priv->vif, hdr->addr1);
			if (sta)
				ieee80211_sta_set_buffered(sta, tid, false);
			rcu_read_unlock();
		}
	}
}