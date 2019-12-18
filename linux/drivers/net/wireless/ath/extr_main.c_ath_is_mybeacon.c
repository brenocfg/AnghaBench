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
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  frame_control; } ;
struct ath_common {int /*<<< orphan*/  curbssid; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal_64bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_zero_ether_addr (int /*<<< orphan*/ ) ; 

bool ath_is_mybeacon(struct ath_common *common, struct ieee80211_hdr *hdr)
{
	return ieee80211_is_beacon(hdr->frame_control) &&
		!is_zero_ether_addr(common->curbssid) &&
		ether_addr_equal_64bits(hdr->addr3, common->curbssid);
}