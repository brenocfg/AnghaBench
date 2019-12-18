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
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_ioctl_set_c_ ; 
 size_t i ; 

u8 rtw_validate_ssid(struct ndis_802_11_ssid *ssid)
{
	u8 ret = true;

	if (ssid->SsidLength > 32) {
		RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("ssid length >32\n"));
		ret = false;
		goto exit;
	}

#ifdef CONFIG_VALIDATE_SSID
	for (i = 0; i < ssid->SsidLength; i++) {
		/* wifi, printable ascii code must be supported */
		if (!((ssid->Ssid[i] >= 0x20) && (ssid->Ssid[i] <= 0x7e))) {
			RT_TRACE(_module_rtl871x_ioctl_set_c_, _drv_err_, ("ssid has non-printable ascii\n"));
			ret = false;
			break;
		}
	}
#endif /* CONFIG_VALIDATE_SSID */

exit:
	return ret;
}