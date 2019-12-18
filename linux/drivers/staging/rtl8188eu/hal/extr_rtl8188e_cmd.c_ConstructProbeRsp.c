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
typedef  int u32 ;
struct wlan_bssid_ex {scalar_t__ ie_length; int /*<<< orphan*/  ies; int /*<<< orphan*/ * MacAddress; } ;
struct mlme_ext_info {struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ frame_control; } ;
struct adapter {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 scalar_t__ MAX_IE_SZ ; 
 int /*<<< orphan*/  SetFrameSubType (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSeqNum (struct ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_PROBERSP ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * myid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ConstructProbeRsp(struct adapter *adapt, u8 *pframe, u32 *pLength, u8 *StaAddr, bool bHideSSID)
{
	struct ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u8 *mac, *bssid;
	u32 pktlen;
	struct mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct wlan_bssid_ex *cur_network = &pmlmeinfo->network;

	pwlanhdr = (struct ieee80211_hdr *)pframe;

	mac = myid(&adapt->eeprompriv);
	bssid = cur_network->MacAddress;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	ether_addr_copy(pwlanhdr->addr1, StaAddr);
	ether_addr_copy(pwlanhdr->addr2, mac);
	ether_addr_copy(pwlanhdr->addr3, bssid);

	SetSeqNum(pwlanhdr, 0);
	SetFrameSubType(fctrl, WIFI_PROBERSP);

	pktlen = sizeof(struct ieee80211_hdr_3addr);
	pframe += pktlen;

	if (cur_network->ie_length > MAX_IE_SZ)
		return;

	memcpy(pframe, cur_network->ies, cur_network->ie_length);
	pframe += cur_network->ie_length;
	pktlen += cur_network->ie_length;

	*pLength = pktlen;
}