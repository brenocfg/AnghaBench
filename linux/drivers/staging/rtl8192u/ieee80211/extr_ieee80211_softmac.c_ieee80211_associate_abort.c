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
struct TYPE_2__ {int /*<<< orphan*/  no_ass_rs; int /*<<< orphan*/  no_auth_rs; } ;
struct ieee80211_device {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  associate_retry_wq; TYPE_1__ softmac_stats; int /*<<< orphan*/  associate_seq; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_ASSOCIATING_AUTHENTICATING ; 
 scalar_t__ IEEE80211_ASSOCIATING_RETRY ; 
 int /*<<< orphan*/  IEEE80211_DEBUG_MGMT (char*) ; 
 int /*<<< orphan*/  IEEE80211_SOFTMAC_ASSOC_RETRY_TIME ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void ieee80211_associate_abort(struct ieee80211_device *ieee)
{
	unsigned long flags;
	spin_lock_irqsave(&ieee->lock, flags);

	ieee->associate_seq++;

	/* don't scan, and avoid to have the RX path possibily
	 * try again to associate. Even do not react to AUTH or
	 * ASSOC response. Just wait for the retry wq to be scheduled.
	 * Here we will check if there are good nets to associate
	 * with, so we retry or just get back to NO_LINK and scanning
	 */
	if (ieee->state == IEEE80211_ASSOCIATING_AUTHENTICATING) {
		IEEE80211_DEBUG_MGMT("Authentication failed\n");
		ieee->softmac_stats.no_auth_rs++;
	} else {
		IEEE80211_DEBUG_MGMT("Association failed\n");
		ieee->softmac_stats.no_ass_rs++;
	}

	ieee->state = IEEE80211_ASSOCIATING_RETRY;

	schedule_delayed_work(&ieee->associate_retry_wq, \
			      IEEE80211_SOFTMAC_ASSOC_RETRY_TIME);

	spin_unlock_irqrestore(&ieee->lock, flags);
}