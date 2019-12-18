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
typedef  scalar_t__ uint ;
struct wlan_bssid_ex {scalar_t__ IELength; } ;

/* Variables and functions */
 scalar_t__ MAX_IE_SZ ; 

uint r8712_get_wlan_bssid_ex_sz(struct wlan_bssid_ex *bss)
{
	return sizeof(*bss) + bss->IELength - MAX_IE_SZ;
}