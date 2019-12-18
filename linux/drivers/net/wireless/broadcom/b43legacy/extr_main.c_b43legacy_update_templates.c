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
struct sk_buff {int dummy; } ;
struct b43legacy_wl {int beacon0_uploaded; int beacon1_uploaded; int /*<<< orphan*/  beacon_update_trigger; int /*<<< orphan*/  hw; struct sk_buff* current_beacon; int /*<<< orphan*/  vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 struct sk_buff* ieee80211_beacon_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void b43legacy_update_templates(struct b43legacy_wl *wl)
{
	struct sk_buff *beacon;
	/* This is the top half of the ansynchronous beacon update. The bottom
	 * half is the beacon IRQ. Beacon update must be asynchronous to avoid
	 * sending an invalid beacon. This can happen for example, if the
	 * firmware transmits a beacon while we are updating it. */

	/* We could modify the existing beacon and set the aid bit in the TIM
	 * field, but that would probably require resizing and moving of data
	 * within the beacon template. Simply request a new beacon and let
	 * mac80211 do the hard work. */
	beacon = ieee80211_beacon_get(wl->hw, wl->vif);
	if (unlikely(!beacon))
		return;

	if (wl->current_beacon)
		dev_kfree_skb_any(wl->current_beacon);
	wl->current_beacon = beacon;
	wl->beacon0_uploaded = false;
	wl->beacon1_uploaded = false;
	ieee80211_queue_work(wl->hw, &wl->beacon_update_trigger);
}