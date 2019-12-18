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
struct timer_list {int dummy; } ;
struct ieee80211_device {int /*<<< orphan*/  beacon_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  beacon_timer ; 
 struct ieee80211_device* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ieee80211_device* ieee ; 
 int /*<<< orphan*/  ieee80211_send_beacon (struct ieee80211_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ieee80211_send_beacon_cb(struct timer_list *t)
{
	struct ieee80211_device *ieee =
		from_timer(ieee, t, beacon_timer);
	unsigned long flags;

	spin_lock_irqsave(&ieee->beacon_lock, flags);
	ieee80211_send_beacon(ieee);
	spin_unlock_irqrestore(&ieee->beacon_lock, flags);
}