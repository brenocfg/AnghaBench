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
struct ndis_802_11_ssid {int SsidLength; int* Ssid; } ;

/* Variables and functions */

__attribute__((used)) static u8 validate_ssid(struct ndis_802_11_ssid *ssid)
{
	u8 i;

	if (ssid->SsidLength > 32)
		return false;
	for (i = 0; i < ssid->SsidLength; i++) {
		/* wifi, printable ascii code must be supported */
		if (!((ssid->Ssid[i] >= 0x20) && (ssid->Ssid[i] <= 0x7e)))
			return false;
	}
	return true;
}