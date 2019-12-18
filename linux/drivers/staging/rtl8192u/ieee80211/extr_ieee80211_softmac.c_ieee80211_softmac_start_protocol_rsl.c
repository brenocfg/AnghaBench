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
struct ieee80211_device {int /*<<< orphan*/  wx_mutex; scalar_t__ sync_scan_hurryup; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_start_protocol (struct ieee80211_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void ieee80211_softmac_start_protocol(struct ieee80211_device *ieee)
{
	ieee->sync_scan_hurryup = 0;
	mutex_lock(&ieee->wx_mutex);
	ieee80211_start_protocol(ieee);
	mutex_unlock(&ieee->wx_mutex);
}