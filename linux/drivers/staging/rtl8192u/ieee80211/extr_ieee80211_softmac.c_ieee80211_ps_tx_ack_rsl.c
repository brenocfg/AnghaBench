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
struct ieee80211_device {int sta_sleep; int /*<<< orphan*/  lock; int /*<<< orphan*/  mgmt_tx_lock; int /*<<< orphan*/  ps_tl; int /*<<< orphan*/  ps_th; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* enter_sleep_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_sta_ps_send_null_frame (struct ieee80211_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_ps_tx_ack(struct ieee80211_device *ieee, short success)
{
	unsigned long flags, flags2;

	spin_lock_irqsave(&ieee->lock, flags);

	if (ieee->sta_sleep == 2) {
		/* Null frame with PS bit set */
		if (success) {
			ieee->sta_sleep = 1;
			ieee->enter_sleep_state(ieee->dev, ieee->ps_th, ieee->ps_tl);
		}
		/* if the card report not success we can't be sure the AP
		 * has not RXed so we can't assume the AP believe us awake
		 */
	} else {
		/* 21112005 - tx again null without PS bit if lost */
		if ((ieee->sta_sleep == 0) && !success) {
			spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);
			ieee80211_sta_ps_send_null_frame(ieee, 0);
			spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
		}
	}
	spin_unlock_irqrestore(&ieee->lock, flags);
}