#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct TYPE_3__ {int /*<<< orphan*/  rx_mcs_map; } ;
struct TYPE_4__ {TYPE_1__ vht_mcs; } ;
struct ieee80211_sta {TYPE_2__ vht_cap; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 get_vht_ra_mask(struct ieee80211_sta *sta)
{
	u64 ra_mask = 0;
	u16 mcs_map = le16_to_cpu(sta->vht_cap.vht_mcs.rx_mcs_map);
	u8 vht_mcs_cap;
	int i, nss;

	/* 4SS, every two bits for MCS7/8/9 */
	for (i = 0, nss = 12; i < 4; i++, mcs_map >>= 2, nss += 10) {
		vht_mcs_cap = mcs_map & 0x3;
		switch (vht_mcs_cap) {
		case 2: /* MCS9 */
			ra_mask |= 0x3ffULL << nss;
			break;
		case 1: /* MCS8 */
			ra_mask |= 0x1ffULL << nss;
			break;
		case 0: /* MCS7 */
			ra_mask |= 0x0ffULL << nss;
			break;
		default:
			break;
		}
	}

	return ra_mask;
}