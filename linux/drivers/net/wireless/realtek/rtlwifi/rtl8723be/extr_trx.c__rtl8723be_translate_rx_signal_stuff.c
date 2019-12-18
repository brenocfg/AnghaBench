#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/ * data; } ;
struct rx_fwinfo_8723be {int dummy; } ;
struct rtl_stats {int rx_drvinfo_size; int rx_bufshift; int /*<<< orphan*/  icv; int /*<<< orphan*/  crc; int /*<<< orphan*/  hwerror; int /*<<< orphan*/  psaddr; } ;
struct rtl_mac {int /*<<< orphan*/ * bssid; } ;
struct rtl_efuse {int /*<<< orphan*/ * dev_addr; } ;
struct ieee80211_hw {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/ * addr3; int /*<<< orphan*/ * addr2; int /*<<< orphan*/ * addr1; } ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_6__ {int /*<<< orphan*/  num_qry_beacon_pkt; } ;
struct TYPE_7__ {TYPE_1__ dbginfo; } ;
struct TYPE_8__ {TYPE_2__ dm; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ IEEE80211_FCTL_FROMDS ; 
 scalar_t__ IEEE80211_FCTL_TODS ; 
 scalar_t__ IEEE80211_FTYPE_CTL ; 
 scalar_t__ WLAN_FC_GET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl8723be_query_rxphystatus (struct ieee80211_hw*,struct rtl_stats*,int /*<<< orphan*/ *,struct rx_fwinfo_8723be*,int,int,int) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ieee80211_get_SA (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_beacon (int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct rtl_efuse* rtl_efuse (TYPE_3__*) ; 
 struct rtl_mac* rtl_mac (TYPE_3__*) ; 
 TYPE_3__* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_process_phyinfo (struct ieee80211_hw*,int /*<<< orphan*/ *,struct rtl_stats*) ; 

__attribute__((used)) static void _rtl8723be_translate_rx_signal_stuff(struct ieee80211_hw *hw,
					struct sk_buff *skb,
					struct rtl_stats *pstatus,
					__le32 *pdesc,
					struct rx_fwinfo_8723be *p_drvinfo)
{
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	struct rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	struct ieee80211_hdr *hdr;
	u8 *tmp_buf;
	u8 *praddr;
	u8 *psaddr;
	u16 fc, type;
	bool packet_matchbssid, packet_toself, packet_beacon;

	tmp_buf = skb->data + pstatus->rx_drvinfo_size + pstatus->rx_bufshift;

	hdr = (struct ieee80211_hdr *)tmp_buf;
	fc = le16_to_cpu(hdr->frame_control);
	type = WLAN_FC_GET_TYPE(hdr->frame_control);
	praddr = hdr->addr1;
	psaddr = ieee80211_get_SA(hdr);
	memcpy(pstatus->psaddr, psaddr, ETH_ALEN);

	packet_matchbssid = ((IEEE80211_FTYPE_CTL != type) &&
	     (ether_addr_equal(mac->bssid, (fc & IEEE80211_FCTL_TODS) ?
				  hdr->addr1 : (fc & IEEE80211_FCTL_FROMDS) ?
				  hdr->addr2 : hdr->addr3)) &&
				  (!pstatus->hwerror) &&
				  (!pstatus->crc) && (!pstatus->icv));

	packet_toself = packet_matchbssid &&
	    (ether_addr_equal(praddr, rtlefuse->dev_addr));

	/* YP: packet_beacon is not initialized,
	 * this assignment is neccesary,
	 * otherwise it counld be true in this case
	 * the situation is much worse in Kernel 3.10
	 */
	if (ieee80211_is_beacon(hdr->frame_control))
		packet_beacon = true;
	else
		packet_beacon = false;

	if (packet_beacon && packet_matchbssid)
		rtl_priv(hw)->dm.dbginfo.num_qry_beacon_pkt++;

	_rtl8723be_query_rxphystatus(hw, pstatus, pdesc, p_drvinfo,
				     packet_matchbssid,
				     packet_toself,
				     packet_beacon);

	rtl_process_phyinfo(hw, tmp_buf, pstatus);
}