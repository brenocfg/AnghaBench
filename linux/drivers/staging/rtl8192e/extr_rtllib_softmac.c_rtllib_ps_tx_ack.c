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
struct rtllib_device {scalar_t__ sta_sleep; int /*<<< orphan*/  lock; int /*<<< orphan*/  mgmt_tx_lock; TYPE_1__* pHTInfo; int /*<<< orphan*/  ps_time; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* enter_sleep_state ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_2__ {int IOTAction; } ;

/* Variables and functions */
 int HT_IOT_ACT_NULL_DATA_POWER_SAVING ; 
 scalar_t__ LPS_IS_SLEEP ; 
 scalar_t__ LPS_IS_WAKE ; 
 scalar_t__ LPS_WAIT_NULL_DATA_SEND ; 
 int /*<<< orphan*/  rtllib_sta_ps_send_null_frame (struct rtllib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtllib_sta_ps_send_pspoll_frame (struct rtllib_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rtllib_ps_tx_ack(struct rtllib_device *ieee, short success)
{
	unsigned long flags, flags2;

	spin_lock_irqsave(&ieee->lock, flags);

	if (ieee->sta_sleep == LPS_WAIT_NULL_DATA_SEND) {
		/* Null frame with PS bit set */
		if (success) {
			ieee->sta_sleep = LPS_IS_SLEEP;
			ieee->enter_sleep_state(ieee->dev, ieee->ps_time);
		}
		/* if the card report not success we can't be sure the AP
		 * has not RXed so we can't assume the AP believe us awake
		 */
	} else {/* 21112005 - tx again null without PS bit if lost */

		if ((ieee->sta_sleep == LPS_IS_WAKE) && !success) {
			spin_lock_irqsave(&ieee->mgmt_tx_lock, flags2);
			if (ieee->pHTInfo->IOTAction &
			    HT_IOT_ACT_NULL_DATA_POWER_SAVING)
				rtllib_sta_ps_send_null_frame(ieee, 0);
			else
				rtllib_sta_ps_send_pspoll_frame(ieee);
			spin_unlock_irqrestore(&ieee->mgmt_tx_lock, flags2);
		}
	}
	spin_unlock_irqrestore(&ieee->lock, flags);
}