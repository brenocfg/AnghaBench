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
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct rx_fwinfo_88e {int dummy; } ;
struct rtl_stats {int rx_drvinfo_size; int rx_bufshift; int /*<<< orphan*/  icv; int /*<<< orphan*/  crc; int /*<<< orphan*/  hwerror; int /*<<< orphan*/  psaddr; } ;
struct rtl_mac {int /*<<< orphan*/ * bssid; } ;
struct rtl_efuse {int /*<<< orphan*/ * dev_addr; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/ * addr3; int /*<<< orphan*/ * addr2; int /*<<< orphan*/ * addr1; } ;
typedef  int /*<<< orphan*/  __le32 ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  _rtl88ee_query_rxphystatus (struct ieee80211_hw*,struct rtl_stats*,int /*<<< orphan*/ *,struct rx_fwinfo_88e*,int,int,int) ; 
 int /*<<< orphan*/  _rtl88ee_smart_antenna (struct ieee80211_hw*,struct rtl_stats*) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ieee80211_get_SA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_has_fromds (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_has_tods (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_ctl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (int /*<<< orphan*/ ) ; 
 struct rtl_mac* rtl_mac (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_process_phyinfo (struct ieee80211_hw*,int /*<<< orphan*/ *,struct rtl_stats*) ; 

__attribute__((used)) static void _rtl88ee_translate_rx_signal_stuff(struct ieee80211_hw *hw,
					       struct sk_buff *skb,
					       struct rtl_stats *pstatus,
					       __le32 *pdesc,
					       struct rx_fwinfo_88e *p_drvinfo)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct ieee80211_hdr *hdr;
	u8 *tmp_buf;
	u8 *praddr;
	u8 *psaddr;
	__le16 fc;
	bool packet_matchbssid, packet_toself, packet_beacon;

	tmp_buf = skb->data + pstatus->rx_drvinfo_size + pstatus->rx_bufshift;

	hdr = (struct ieee80211_hdr *)tmp_buf;
	fc = hdr->frame_control;
	praddr = hdr->addr1;
	psaddr = ieee80211_get_SA(hdr);
	memcpy(pstatus->psaddr, psaddr, ETH_ALEN);

	packet_matchbssid = ((!ieee80211_is_ctl(fc)) &&
	     (ether_addr_equal(mac->bssid, ieee80211_has_tods(fc) ?
			       hdr->addr1 : ieee80211_has_fromds(fc) ?
			       hdr->addr2 : hdr->addr3)) &&
			       (!pstatus->hwerror) &&
			       (!pstatus->crc) && (!pstatus->icv));

	packet_toself = packet_matchbssid &&
	    (ether_addr_equal(praddr, rtlefuse->dev_addr));

	if (ieee80211_is_beacon(hdr->frame_control))
		packet_beacon = true;
	else
		packet_beacon = false;

	_rtl88ee_query_rxphystatus(hw, pstatus, pdesc, p_drvinfo,
				   packet_matchbssid, packet_toself,
				   packet_beacon);
	_rtl88ee_smart_antenna(hw, pstatus);
	rtl_process_phyinfo(hw, tmp_buf, pstatus);
}