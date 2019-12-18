#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_7__ {int SignalQuality; int SignalStrength; } ;
struct wlan_bssid_ex {long Rssi; TYPE_3__ PhyInfo; } ;
struct TYPE_6__ {int signal_strength; int signal_qual; } ;
struct TYPE_5__ {int /*<<< orphan*/  network; } ;
struct TYPE_8__ {TYPE_1__ cur_network; } ;
struct adapter {TYPE_2__ recvpriv; TYPE_4__ mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_wlan_bssid_ex_sz (struct wlan_bssid_ex*) ; 
 scalar_t__ is_same_network (int /*<<< orphan*/ *,struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_antdiv_rssi_compared (struct adapter*,struct wlan_bssid_ex*,struct wlan_bssid_ex*) ; 

void update_network(struct wlan_bssid_ex *dst, struct wlan_bssid_ex *src,
	struct adapter *padapter, bool update_ie)
{
	long rssi_ori = dst->Rssi;
	u8 sq_smp = src->PhyInfo.SignalQuality;
	u8 ss_final;
	u8 sq_final;
	long rssi_final;

	rtw_hal_antdiv_rssi_compared(padapter, dst, src); /* this will update src.Rssi, need consider again */

	/* The rule below is 1/5 for sample value, 4/5 for history value */
	if (check_fwstate(&padapter->mlmepriv, _FW_LINKED) &&
	    is_same_network(&padapter->mlmepriv.cur_network.network, src)) {
		/* Take the recvpriv's value for the connected AP*/
		ss_final = padapter->recvpriv.signal_strength;
		sq_final = padapter->recvpriv.signal_qual;
		/* the rssi value here is undecorated, and will be used for antenna diversity */
		if (sq_smp != 101) /* from the right channel */
			rssi_final = (src->Rssi + dst->Rssi * 4) / 5;
		else
			rssi_final = rssi_ori;
	} else {
		if (sq_smp != 101) { /* from the right channel */
			ss_final = ((u32)(src->PhyInfo.SignalStrength)+(u32)(dst->PhyInfo.SignalStrength)*4)/5;
			sq_final = ((u32)(src->PhyInfo.SignalQuality)+(u32)(dst->PhyInfo.SignalQuality)*4)/5;
			rssi_final = (src->Rssi+dst->Rssi*4)/5;
		} else {
			/* bss info not receiving from the right channel, use the original RX signal infos */
			ss_final = dst->PhyInfo.SignalStrength;
			sq_final = dst->PhyInfo.SignalQuality;
			rssi_final = dst->Rssi;
		}
	}
	if (update_ie)
		memcpy((u8 *)dst, (u8 *)src, get_wlan_bssid_ex_sz(src));
	dst->PhyInfo.SignalStrength = ss_final;
	dst->PhyInfo.SignalQuality = sq_final;
	dst->Rssi = rssi_final;
}