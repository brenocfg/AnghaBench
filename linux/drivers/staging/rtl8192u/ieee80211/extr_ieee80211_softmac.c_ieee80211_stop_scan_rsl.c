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
struct ieee80211_device {int softmac_features; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* stop_scan ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int IEEE_SOFTMAC_SCAN ; 
 int /*<<< orphan*/  ieee80211_softmac_stop_scan (struct ieee80211_device*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void ieee80211_stop_scan(struct ieee80211_device *ieee)
{
	if (ieee->softmac_features & IEEE_SOFTMAC_SCAN)
		ieee80211_softmac_stop_scan(ieee);
	else
		ieee->stop_scan(ieee->dev);
}