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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {void* len; void* type; } ;
struct mrvl_ie_rates_param_set {TYPE_1__ header; } ;
struct cfg80211_bss {int dummy; } ;

/* Variables and functions */
 int TLV_TYPE_RATES ; 
 int /*<<< orphan*/  WLAN_EID_EXT_SUPP_RATES ; 
 int /*<<< orphan*/  WLAN_EID_SUPP_RATES ; 
 int /*<<< orphan*/ * add_ie_rates (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int*) ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/ * ieee80211_bss_get_ie (struct cfg80211_bss*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_deb_assoc (char*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static int lbs_add_common_rates_tlv(u8 *tlv, struct cfg80211_bss *bss)
{
	struct mrvl_ie_rates_param_set *rate_tlv = (void *)tlv;
	const u8 *rates_eid, *ext_rates_eid;
	int n = 0;

	rcu_read_lock();
	rates_eid = ieee80211_bss_get_ie(bss, WLAN_EID_SUPP_RATES);
	ext_rates_eid = ieee80211_bss_get_ie(bss, WLAN_EID_EXT_SUPP_RATES);

	/*
	 * 01 00                   TLV_TYPE_RATES
	 * 04 00                   len
	 * 82 84 8b 96             rates
	 */
	rate_tlv->header.type = cpu_to_le16(TLV_TYPE_RATES);
	tlv += sizeof(rate_tlv->header);

	/* Add basic rates */
	if (rates_eid) {
		tlv = add_ie_rates(tlv, rates_eid, &n);

		/* Add extended rates, if any */
		if (ext_rates_eid)
			tlv = add_ie_rates(tlv, ext_rates_eid, &n);
	} else {
		lbs_deb_assoc("assoc: bss had no basic rate IE\n");
		/* Fallback: add basic 802.11b rates */
		*tlv++ = 0x82;
		*tlv++ = 0x84;
		*tlv++ = 0x8b;
		*tlv++ = 0x96;
		n = 4;
	}
	rcu_read_unlock();

	rate_tlv->header.len = cpu_to_le16(n);
	return sizeof(rate_tlv->header) + n;
}