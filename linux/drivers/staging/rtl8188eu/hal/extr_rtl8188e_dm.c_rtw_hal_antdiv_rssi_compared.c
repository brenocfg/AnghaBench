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
struct TYPE_4__ {int /*<<< orphan*/  Optimum_antenna; } ;
struct wlan_bssid_ex {scalar_t__ Rssi; TYPE_2__ PhyInfo; } ;
struct adapter {TYPE_1__* HalData; } ;
struct TYPE_3__ {scalar_t__ AntDivCfg; } ;

/* Variables and functions */

void rtw_hal_antdiv_rssi_compared(struct adapter *Adapter, struct wlan_bssid_ex *dst, struct wlan_bssid_ex *src)
{
	if (Adapter->HalData->AntDivCfg != 0) {
		/* select optimum_antenna for before linked =>For antenna diversity */
		if (dst->Rssi >=  src->Rssi) {/* keep org parameter */
			src->Rssi = dst->Rssi;
			src->PhyInfo.Optimum_antenna = dst->PhyInfo.Optimum_antenna;
		}
	}
}