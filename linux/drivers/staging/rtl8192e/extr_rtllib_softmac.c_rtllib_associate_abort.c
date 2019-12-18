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
struct rtllib_device {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  associate_retry_wq; TYPE_1__ softmac_stats; int /*<<< orphan*/  dev; int /*<<< orphan*/  associate_seq; } ;

/* Variables and functions */
 scalar_t__ RTLLIB_ASSOCIATING_AUTHENTICATING ; 
 scalar_t__ RTLLIB_ASSOCIATING_RETRY ; 
 int /*<<< orphan*/  RTLLIB_SOFTMAC_ASSOC_RETRY_TIME ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void rtllib_associate_abort(struct rtllib_device *ieee)
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
	if (ieee->state == RTLLIB_ASSOCIATING_AUTHENTICATING) {
		netdev_dbg(ieee->dev, "Authentication failed\n");
		ieee->softmac_stats.no_auth_rs++;
	} else {
		netdev_dbg(ieee->dev, "Association failed\n");
		ieee->softmac_stats.no_ass_rs++;
	}

	ieee->state = RTLLIB_ASSOCIATING_RETRY;

	schedule_delayed_work(&ieee->associate_retry_wq,
			      RTLLIB_SOFTMAC_ASSOC_RETRY_TIME);

	spin_unlock_irqrestore(&ieee->lock, flags);
}