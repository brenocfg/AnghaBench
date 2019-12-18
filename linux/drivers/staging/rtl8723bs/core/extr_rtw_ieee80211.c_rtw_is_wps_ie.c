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
typedef  int uint ;
typedef  int u8 ;

/* Variables and functions */
 int _WPA_IE_ID_ ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 

u8 rtw_is_wps_ie(u8 *ie_ptr, uint *wps_ielen)
{
	u8 match = false;
	u8 eid, wps_oui[4] = {0x0, 0x50, 0xf2, 0x04};

	if (!ie_ptr)
		return match;

	eid = ie_ptr[0];

	if ((eid == _WPA_IE_ID_) && (!memcmp(&ie_ptr[2], wps_oui, 4))) {
		/* DBG_8192C("==> found WPS_IE.....\n"); */
		*wps_ielen = ie_ptr[1]+2;
		match = true;
	}
	return match;
}