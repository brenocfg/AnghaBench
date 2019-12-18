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
typedef  int /*<<< orphan*/  u8 ;
struct mt7601u_dev {int /*<<< orphan*/  ap_bssid; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt7601u_rx_is_our_beacon(struct mt7601u_dev *dev, u8 *data)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)data;

	return ieee80211_is_beacon(hdr->frame_control) &&
		ether_addr_equal(hdr->addr2, dev->ap_bssid);
}