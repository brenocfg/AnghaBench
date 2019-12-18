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
typedef  int u32 ;
struct TYPE_2__ {int InfrastructureMode; } ;
struct wlan_network {TYPE_1__ network; } ;
struct wlan_bssid_ex {scalar_t__* MacAddress; } ;
struct mlme_priv {struct wlan_network cur_network; } ;
struct mlme_ext_info {struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct ieee80211_qos_hdr {int /*<<< orphan*/  qos_ctrl; } ;
struct ieee80211_hdr_3addr {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ frame_control; } ;
struct adapter {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
#define  Ndis802_11APMode 130 
#define  Ndis802_11IBSS 129 
#define  Ndis802_11Infrastructure 128 
 int /*<<< orphan*/  SetEOSP (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SetFrDs (scalar_t__*) ; 
 int /*<<< orphan*/  SetFrameSubType (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPriority (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  SetPwrMgt (scalar_t__*) ; 
 int /*<<< orphan*/  SetSeqNum (struct ieee80211_hdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetToDs (scalar_t__*) ; 
 int /*<<< orphan*/  WIFI_DATA_NULL ; 
 int /*<<< orphan*/  WIFI_QOS_DATA_NULL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* myid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ConstructNullFunctionData(struct adapter *adapt, u8 *pframe,
	u32 *pLength,
	u8 *StaAddr,
	u8 bQoS,
	u8 AC,
	u8 bEosp,
	u8 bForcePowerSave)
{
	struct ieee80211_hdr *pwlanhdr;
	__le16 *fctrl;
	u32 pktlen;
	struct mlme_priv *pmlmepriv = &adapt->mlmepriv;
	struct wlan_network *cur_network = &pmlmepriv->cur_network;
	struct mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	pwlanhdr = (struct ieee80211_hdr *)pframe;

	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	if (bForcePowerSave)
		SetPwrMgt(fctrl);

	switch (cur_network->network.InfrastructureMode) {
	case Ndis802_11Infrastructure:
		SetToDs(fctrl);
		ether_addr_copy(pwlanhdr->addr1, pnetwork->MacAddress);
		ether_addr_copy(pwlanhdr->addr2, myid(&adapt->eeprompriv));
		ether_addr_copy(pwlanhdr->addr3, StaAddr);
		break;
	case Ndis802_11APMode:
		SetFrDs(fctrl);
		ether_addr_copy(pwlanhdr->addr1, StaAddr);
		ether_addr_copy(pwlanhdr->addr2, pnetwork->MacAddress);
		ether_addr_copy(pwlanhdr->addr3, myid(&adapt->eeprompriv));
		break;
	case Ndis802_11IBSS:
	default:
		ether_addr_copy(pwlanhdr->addr1, StaAddr);
		ether_addr_copy(pwlanhdr->addr2, myid(&adapt->eeprompriv));
		ether_addr_copy(pwlanhdr->addr3, pnetwork->MacAddress);
		break;
	}

	SetSeqNum(pwlanhdr, 0);

	if (bQoS) {
		struct ieee80211_qos_hdr *pwlanqoshdr;

		SetFrameSubType(pframe, WIFI_QOS_DATA_NULL);

		pwlanqoshdr = (struct ieee80211_qos_hdr *)pframe;
		SetPriority(&pwlanqoshdr->qos_ctrl, AC);
		SetEOSP(&pwlanqoshdr->qos_ctrl, bEosp);

		pktlen = sizeof(struct ieee80211_qos_hdr);
	} else {
		SetFrameSubType(pframe, WIFI_DATA_NULL);

		pktlen = sizeof(struct ieee80211_hdr_3addr);
	}

	*pLength = pktlen;
}