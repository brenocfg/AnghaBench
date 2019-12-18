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
typedef  int u8 ;

/* Variables and functions */
 int WFA_TPC_IE_LEN ; 
 int WLAN_EID_VENDOR_SPECIFIC ; 
 int WLAN_OUI_MICROSOFT ; 
 int WLAN_OUI_TYPE_MICROSOFT_TPC ; 

__attribute__((used)) static void iwl_mvm_add_tpc_report_ie(u8 *pos)
{
	pos[0] = WLAN_EID_VENDOR_SPECIFIC;
	pos[1] = WFA_TPC_IE_LEN - 2;
	pos[2] = (WLAN_OUI_MICROSOFT >> 16) & 0xff;
	pos[3] = (WLAN_OUI_MICROSOFT >> 8) & 0xff;
	pos[4] = WLAN_OUI_MICROSOFT & 0xff;
	pos[5] = WLAN_OUI_TYPE_MICROSOFT_TPC;
	pos[6] = 0;
	/* pos[7] - tx power will be inserted by the FW */
	pos[7] = 0;
	pos[8] = 0;
}