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
struct ieee80211_device {int /*<<< orphan*/  wx_mutex; int /*<<< orphan*/  associate_retry_wq; int /*<<< orphan*/  associate_timer; int /*<<< orphan*/ * dot11d_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_softmac_free(struct ieee80211_device *ieee)
{
	mutex_lock(&ieee->wx_mutex);
	kfree(ieee->dot11d_info);
	ieee->dot11d_info = NULL;
	del_timer_sync(&ieee->associate_timer);

	cancel_delayed_work(&ieee->associate_retry_wq);

	mutex_unlock(&ieee->wx_mutex);
}