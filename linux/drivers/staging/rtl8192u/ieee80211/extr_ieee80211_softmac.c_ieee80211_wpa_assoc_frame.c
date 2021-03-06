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
struct ieee80211_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_disassociate (struct ieee80211_device*) ; 
 int /*<<< orphan*/  ieee80211_wpa_enable (struct ieee80211_device*,int) ; 

__attribute__((used)) static void ieee80211_wpa_assoc_frame(struct ieee80211_device *ieee,
				      char *wpa_ie, int wpa_ie_len)
{
	/* make sure WPA is enabled */
	ieee80211_wpa_enable(ieee, 1);

	ieee80211_disassociate(ieee);
}