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
typedef  int u32 ;

/* Variables and functions */
 int RNDIS_WLAN_KEY_MGMT_802_1X ; 
 int RNDIS_WLAN_KEY_MGMT_NONE ; 
 int RNDIS_WLAN_KEY_MGMT_PSK ; 
#define  WLAN_AKM_SUITE_8021X 129 
#define  WLAN_AKM_SUITE_PSK 128 

__attribute__((used)) static int rndis_akm_suite_to_key_mgmt(u32 akm_suite)
{
	switch (akm_suite) {
	default:
		return RNDIS_WLAN_KEY_MGMT_NONE;
	case WLAN_AKM_SUITE_8021X:
		return RNDIS_WLAN_KEY_MGMT_802_1X;
	case WLAN_AKM_SUITE_PSK:
		return RNDIS_WLAN_KEY_MGMT_PSK;
	}
}