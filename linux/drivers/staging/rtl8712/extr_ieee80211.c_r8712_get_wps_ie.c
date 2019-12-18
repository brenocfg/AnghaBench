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
typedef  size_t uint ;
typedef  int u8 ;

/* Variables and functions */
 int _WPA_IE_ID_ ; 
 int /*<<< orphan*/  memcmp (int*,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

int r8712_get_wps_ie(u8 *in_ie, uint in_len, u8 *wps_ie, uint *wps_ielen)
{
	int match;
	uint cnt;
	u8 eid, wps_oui[4] = {0x0, 0x50, 0xf2, 0x04};

	cnt = 12;
	match = false;
	while (cnt < in_len) {
		eid = in_ie[cnt];
		if ((eid == _WPA_IE_ID_) &&
		    (!memcmp(&in_ie[cnt + 2], wps_oui, 4))) {
			memcpy(wps_ie, &in_ie[cnt], in_ie[cnt + 1] + 2);
			*wps_ielen = in_ie[cnt + 1] + 2;
			cnt += in_ie[cnt + 1] + 2;
			match = true;
			break;
		}
		cnt += in_ie[cnt + 1] + 2; /* goto next */
	}
	return match;
}