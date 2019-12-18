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
struct TYPE_2__ {int /*<<< orphan*/  swtxstop; } ;
struct ieee80211_device {int queue_stop; TYPE_1__ softmac_stats; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (int /*<<< orphan*/ ) ; 

void ieee80211_stop_queue(struct ieee80211_device *ieee)
{
	//unsigned long flags;
	//spin_lock_irqsave(&ieee->lock,flags);

	if (!netif_queue_stopped(ieee->dev)) {
		netif_stop_queue(ieee->dev);
		ieee->softmac_stats.swtxstop++;
	}
	ieee->queue_stop = 1;
	//spin_unlock_irqrestore(&ieee->lock,flags);
}