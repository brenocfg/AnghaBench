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
typedef  scalar_t__ u8 ;
struct sk_buff {int len; scalar_t__* data; } ;
struct rtl_80211_hdr_3addr {int /*<<< orphan*/  addr2; } ;
struct TYPE_2__ {int /*<<< orphan*/  ssid; } ;
struct ieee80211_device {TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (scalar_t__*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static short probe_rq_parse(struct ieee80211_device *ieee, struct sk_buff *skb, u8 *src)
{
	u8 *tag;
	u8 *skbend;
	u8 *ssid = NULL;
	u8 ssidlen = 0;

	struct rtl_80211_hdr_3addr   *header =
		(struct rtl_80211_hdr_3addr   *)skb->data;

	if (skb->len < sizeof(struct rtl_80211_hdr_3addr))
		return -1; /* corrupted */

	memcpy(src, header->addr2, ETH_ALEN);

	skbend = (u8 *)skb->data + skb->len;

	tag = skb->data + sizeof(struct rtl_80211_hdr_3addr);

	while (tag + 1 < skbend) {
		if (*tag == 0) {
			ssid = tag + 2;
			ssidlen = *(tag + 1);
			break;
		}
		tag++; /* point to the len field */
		tag = tag + *(tag); /* point to the last data byte of the tag */
		tag++; /* point to the next tag */
	}

	//IEEE80211DMESG("Card MAC address is "MACSTR, MAC2STR(src));
	if (ssidlen == 0)
		return 1;

	if (!ssid)
		return 1; /* ssid not found in tagged param */

	return (!strncmp(ssid, ieee->current_network.ssid, ssidlen));
}