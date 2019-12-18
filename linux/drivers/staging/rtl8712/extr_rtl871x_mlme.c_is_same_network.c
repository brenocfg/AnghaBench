#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_4__ {scalar_t__ SsidLength; int /*<<< orphan*/  Ssid; } ;
struct TYPE_3__ {scalar_t__ DSConfig; } ;
struct wlan_bssid_ex {TYPE_2__ Ssid; int /*<<< orphan*/  MacAddress; TYPE_1__ Configuration; int /*<<< orphan*/  IEs; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int WLAN_CAPABILITY_BSS ; 
 int WLAN_CAPABILITY_IBSS ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8712_get_capability_from_ie (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_same_network(struct wlan_bssid_ex *src,
			   struct wlan_bssid_ex *dst)
{
	u16 s_cap, d_cap;

	memcpy((u8 *)&s_cap, r8712_get_capability_from_ie(src->IEs), 2);
	memcpy((u8 *)&d_cap, r8712_get_capability_from_ie(dst->IEs), 2);
	return (src->Ssid.SsidLength == dst->Ssid.SsidLength) &&
			(src->Configuration.DSConfig ==
			dst->Configuration.DSConfig) &&
			((!memcmp(src->MacAddress, dst->MacAddress,
			ETH_ALEN))) &&
			((!memcmp(src->Ssid.Ssid,
			  dst->Ssid.Ssid,
			  src->Ssid.SsidLength))) &&
			((s_cap & WLAN_CAPABILITY_IBSS) ==
			(d_cap & WLAN_CAPABILITY_IBSS)) &&
			((s_cap & WLAN_CAPABILITY_BSS) ==
			(d_cap & WLAN_CAPABILITY_BSS));

}