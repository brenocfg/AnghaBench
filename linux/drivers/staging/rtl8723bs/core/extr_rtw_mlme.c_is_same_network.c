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
typedef  int u16 ;
struct TYPE_2__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct wlan_bssid_ex {TYPE_1__ Ssid; int /*<<< orphan*/  MacAddress; int /*<<< orphan*/  IEs; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int WLAN_CAPABILITY_BSS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int rtw_bug_check (struct wlan_bssid_ex*,struct wlan_bssid_ex*,int*,int*) ; 
 int /*<<< orphan*/  rtw_get_capability_from_ie (int /*<<< orphan*/ ) ; 

int is_same_network(struct wlan_bssid_ex *src, struct wlan_bssid_ex *dst, u8 feature)
{
	u16 s_cap, d_cap;
	__le16 tmps, tmpd;

	if (rtw_bug_check(dst, src, &s_cap, &d_cap) == false)
			return false;

	memcpy((u8 *)&tmps, rtw_get_capability_from_ie(src->IEs), 2);
	memcpy((u8 *)&tmpd, rtw_get_capability_from_ie(dst->IEs), 2);


	s_cap = le16_to_cpu(tmps);
	d_cap = le16_to_cpu(tmpd);

	return (src->Ssid.SsidLength == dst->Ssid.SsidLength) &&
		/* 	(src->Configuration.DSConfig == dst->Configuration.DSConfig) && */
			((!memcmp(src->MacAddress, dst->MacAddress, ETH_ALEN))) &&
			((!memcmp(src->Ssid.Ssid, dst->Ssid.Ssid, src->Ssid.SsidLength))) &&
			((s_cap & WLAN_CAPABILITY_IBSS) ==
			(d_cap & WLAN_CAPABILITY_IBSS)) &&
			((s_cap & WLAN_CAPABILITY_BSS) ==
			(d_cap & WLAN_CAPABILITY_BSS));

}