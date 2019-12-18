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
struct TYPE_2__ {int /*<<< orphan*/  fc; } ;
union p80211_hdr {TYPE_1__ a3; } ;
struct wlandevice {int hostwep; struct hfa384x* priv; } ;
struct sk_buff {int dummy; } ;
struct p80211_metawep {int dummy; } ;
struct hfa384x {int dummy; } ;

/* Variables and functions */
 int HOSTWEP_ENCRYPT ; 
 int HOSTWEP_PRIVACYINVOKED ; 
 int /*<<< orphan*/  WLAN_SET_FC_ISWEP (int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hfa384x_drvr_txframe (struct hfa384x*,struct sk_buff*,union p80211_hdr*,struct p80211_metawep*) ; 

__attribute__((used)) static int prism2sta_txframe(struct wlandevice *wlandev, struct sk_buff *skb,
			     union p80211_hdr *p80211_hdr,
			     struct p80211_metawep *p80211_wep)
{
	struct hfa384x *hw = wlandev->priv;

	/* If necessary, set the 802.11 WEP bit */
	if ((wlandev->hostwep & (HOSTWEP_PRIVACYINVOKED | HOSTWEP_ENCRYPT)) ==
	    HOSTWEP_PRIVACYINVOKED) {
		p80211_hdr->a3.fc |= cpu_to_le16(WLAN_SET_FC_ISWEP(1));
	}

	return hfa384x_drvr_txframe(hw, skb, p80211_hdr, p80211_wep);
}