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
struct wlan_bssid_ex {int /*<<< orphan*/  MacAddress; } ;
struct mlme_ext_info {int aid; struct wlan_bssid_ex network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct ieee80211_hdr {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ frame_control; } ;
struct adapter {int /*<<< orphan*/  eeprompriv; struct mlme_ext_priv mlmeextpriv; } ;
typedef  scalar_t__ __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  SetDuration (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetFrameSubType (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPwrMgt (scalar_t__*) ; 
 int /*<<< orphan*/  WIFI_PSPOLL ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  myid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ConstructPSPoll(struct adapter *adapt, u8 *pframe, u32 *pLength)
{
	struct ieee80211_hdr *pwlanhdr;
	struct mlme_ext_priv *pmlmeext = &adapt->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	__le16 *fctrl;
	struct wlan_bssid_ex *pnetwork = &pmlmeinfo->network;

	pwlanhdr = (struct ieee80211_hdr *)pframe;

	/*  Frame control. */
	fctrl = &pwlanhdr->frame_control;
	*(fctrl) = 0;
	SetPwrMgt(fctrl);
	SetFrameSubType(pframe, WIFI_PSPOLL);

	/*  AID. */
	SetDuration(pframe, (pmlmeinfo->aid | 0xc000));

	/*  BSSID. */
	ether_addr_copy(pwlanhdr->addr1, pnetwork->MacAddress);

	/*  TA. */
	ether_addr_copy(pwlanhdr->addr2, myid(&adapt->eeprompriv));

	*pLength = 16;
}