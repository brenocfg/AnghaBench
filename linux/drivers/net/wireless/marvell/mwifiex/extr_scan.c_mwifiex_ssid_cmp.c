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
struct cfg80211_ssid {scalar_t__ ssid_len; int /*<<< orphan*/  ssid; } ;
typedef  int s32 ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

s32
mwifiex_ssid_cmp(struct cfg80211_ssid *ssid1, struct cfg80211_ssid *ssid2)
{
	if (!ssid1 || !ssid2 || (ssid1->ssid_len != ssid2->ssid_len))
		return -1;
	return memcmp(ssid1->ssid, ssid2->ssid, ssid1->ssid_len);
}