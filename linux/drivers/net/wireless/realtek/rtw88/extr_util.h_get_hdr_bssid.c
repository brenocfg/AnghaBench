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
struct ieee80211_hdr {int /*<<< orphan*/ * addr3; int /*<<< orphan*/ * addr2; int /*<<< orphan*/ * addr1; int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ ieee80211_has_fromds (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_tods (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 *get_hdr_bssid(struct ieee80211_hdr *hdr)
{
	__le16 fc = hdr->frame_control;
	u8 *bssid;

	if (ieee80211_has_tods(fc))
		bssid = hdr->addr1;
	else if (ieee80211_has_fromds(fc))
		bssid = hdr->addr2;
	else
		bssid = hdr->addr3;

	return bssid;
}