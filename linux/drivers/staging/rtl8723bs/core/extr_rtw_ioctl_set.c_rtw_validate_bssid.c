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
 scalar_t__ is_broadcast_mac_addr (int*) ; 
 scalar_t__ is_multicast_mac_addr (int*) ; 
 scalar_t__ is_zero_mac_addr (int*) ; 

u8 rtw_validate_bssid(u8 *bssid)
{
	u8 ret = true;

	if (is_zero_mac_addr(bssid)
		|| is_broadcast_mac_addr(bssid)
		|| is_multicast_mac_addr(bssid)
	) {
		ret = false;
	}

	return ret;
}