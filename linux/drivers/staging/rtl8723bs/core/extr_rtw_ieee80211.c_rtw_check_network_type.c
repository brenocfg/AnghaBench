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

/* Variables and functions */
 int WIRELESS_11A ; 
 int WIRELESS_11B ; 
 int WIRELESS_11BG ; 
 int WIRELESS_11G ; 
 int WIRELESS_INVALID ; 
 scalar_t__ rtw_is_cckrates_included (unsigned char*) ; 
 scalar_t__ rtw_is_cckratesonly_included (unsigned char*) ; 

int rtw_check_network_type(unsigned char *rate, int ratelen, int channel)
{
	if (channel > 14) {
		if (rtw_is_cckrates_included(rate))
			return WIRELESS_INVALID;
		else
			return WIRELESS_11A;
	} else { /*  could be pure B, pure G, or B/G */
		if (rtw_is_cckratesonly_included(rate))
			return WIRELESS_11B;
		else if (rtw_is_cckrates_included(rate))
			return	WIRELESS_11BG;
		else
			return WIRELESS_11G;
	}
}