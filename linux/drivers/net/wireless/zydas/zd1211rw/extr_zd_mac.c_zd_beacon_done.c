#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  last_update; } ;
struct zd_mac {int /*<<< orphan*/  lock; TYPE_1__ beacon; int /*<<< orphan*/  hw; TYPE_2__* vif; int /*<<< orphan*/  flags; } ;
struct sk_buff {int dummy; } ;
struct TYPE_5__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  ZD_DEVICE_RUNNING ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct sk_buff* ieee80211_get_buffered_bc (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ieee80211_queue_stopped (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zd_mac_config_beacon (int /*<<< orphan*/ ,struct sk_buff*,int) ; 
 int /*<<< orphan*/  zd_op_tx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static void zd_beacon_done(struct zd_mac *mac)
{
	struct sk_buff *skb, *beacon;

	if (!test_bit(ZD_DEVICE_RUNNING, &mac->flags))
		return;
	if (!mac->vif || mac->vif->type != NL80211_IFTYPE_AP)
		return;

	/*
	 * Send out buffered broad- and multicast frames.
	 */
	while (!ieee80211_queue_stopped(mac->hw, 0)) {
		skb = ieee80211_get_buffered_bc(mac->hw, mac->vif);
		if (!skb)
			break;
		zd_op_tx(mac->hw, NULL, skb);
	}

	/*
	 * Fetch next beacon so that tim_count is updated.
	 */
	beacon = ieee80211_beacon_get(mac->hw, mac->vif);
	if (beacon)
		zd_mac_config_beacon(mac->hw, beacon, true);

	spin_lock_irq(&mac->lock);
	mac->beacon.last_update = jiffies;
	spin_unlock_irq(&mac->lock);
}