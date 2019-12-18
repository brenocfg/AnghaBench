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
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  enum ath5k_pkt_type { ____Placeholder_ath5k_pkt_type } ath5k_pkt_type ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int AR5K_PKT_TYPE_ATIM ; 
 int AR5K_PKT_TYPE_BEACON ; 
 int AR5K_PKT_TYPE_NORMAL ; 
 int AR5K_PKT_TYPE_PROBE_RESP ; 
 int AR5K_PKT_TYPE_PSPOLL ; 
 scalar_t__ ieee80211_is_atim (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_probe_resp (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_pspoll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum ath5k_pkt_type get_hw_packet_type(struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr;
	enum ath5k_pkt_type htype;
	__le16 fc;

	hdr = (struct ieee80211_hdr *)skb->data;
	fc = hdr->frame_control;

	if (ieee80211_is_beacon(fc))
		htype = AR5K_PKT_TYPE_BEACON;
	else if (ieee80211_is_probe_resp(fc))
		htype = AR5K_PKT_TYPE_PROBE_RESP;
	else if (ieee80211_is_atim(fc))
		htype = AR5K_PKT_TYPE_ATIM;
	else if (ieee80211_is_pspoll(fc))
		htype = AR5K_PKT_TYPE_PSPOLL;
	else
		htype = AR5K_PKT_TYPE_NORMAL;

	return htype;
}