#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_4__ {scalar_t__ DSConfig; } ;
struct wlan_bssid_ex {TYPE_1__ Configuration; } ;
struct mlme_ext_info {int state; int /*<<< orphan*/  bcn_interval; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {int cur_channel; struct mlme_ext_info mlmext_info; } ;
struct TYPE_5__ {int* MacAddress; } ;
struct TYPE_6__ {TYPE_2__ dev_network; } ;
struct adapter {TYPE_3__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  DBG_871X (char*,unsigned short) ; 
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_DO_IQK ; 
 int /*<<< orphan*/  HW_VAR_MLME_JOIN ; 
 int /*<<< orphan*/  HW_VAR_SEC_CFG ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Set_MSR (struct adapter*,int) ; 
 int WIFI_FW_ADHOC_STATE ; 
 int WIFI_FW_ASSOC_SUCCESS ; 
 int WIFI_FW_NULL_STATE ; 
 scalar_t__ _FAIL ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int /*<<< orphan*/  beacon_timing_control (struct adapter*) ; 
 unsigned short cap_IBSS ; 
 int /*<<< orphan*/  get_beacon_interval (struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  report_join_res (struct adapter*,int) ; 
 unsigned short rtw_get_capability (struct wlan_bssid_ex*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_indicate_connect (struct adapter*) ; 
 scalar_t__ send_beacon (struct adapter*) ; 
 int /*<<< orphan*/  set_channel_bwmode (struct adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_bmc_sta (struct adapter*) ; 
 int /*<<< orphan*/  update_capinfo (struct adapter*,unsigned short) ; 
 int /*<<< orphan*/  update_wireless_mode (struct adapter*) ; 

void start_create_ibss(struct adapter *padapter)
{
	unsigned short	caps;
	u8 val8;
	u8 join_type;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	struct wlan_bssid_ex		*pnetwork = (struct wlan_bssid_ex *)(&(pmlmeinfo->network));
	pmlmeext->cur_channel = (u8)pnetwork->Configuration.DSConfig;
	pmlmeinfo->bcn_interval = get_beacon_interval(pnetwork);

	/* update wireless mode */
	update_wireless_mode(padapter);

	/* udpate capability */
	caps = rtw_get_capability((struct wlan_bssid_ex *)pnetwork);
	update_capinfo(padapter, caps);
	if (caps&cap_IBSS) {/* adhoc master */
		val8 = 0xcf;
		rtw_hal_set_hwreg(padapter, HW_VAR_SEC_CFG, (u8 *)(&val8));

		rtw_hal_set_hwreg(padapter, HW_VAR_DO_IQK, NULL);

		/* switch channel */
		/* SelectChannel(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE); */
		set_channel_bwmode(padapter, pmlmeext->cur_channel, HAL_PRIME_CHNL_OFFSET_DONT_CARE, CHANNEL_WIDTH_20);

		beacon_timing_control(padapter);

		/* set msr to WIFI_FW_ADHOC_STATE */
		pmlmeinfo->state = WIFI_FW_ADHOC_STATE;
		Set_MSR(padapter, (pmlmeinfo->state & 0x3));

		/* issue beacon */
		if (send_beacon(padapter) == _FAIL) {
			RT_TRACE(_module_rtl871x_mlme_c_, _drv_err_, ("issuing beacon frame fail....\n"));

			report_join_res(padapter, -1);
			pmlmeinfo->state = WIFI_FW_NULL_STATE;
		} else {
			rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, padapter->registrypriv.dev_network.MacAddress);
			join_type = 0;
			rtw_hal_set_hwreg(padapter, HW_VAR_MLME_JOIN, (u8 *)(&join_type));

			report_join_res(padapter, 1);
			pmlmeinfo->state |= WIFI_FW_ASSOC_SUCCESS;
			rtw_indicate_connect(padapter);
		}
	} else {
		DBG_871X("start_create_ibss, invalid cap:%x\n", caps);
		return;
	}
	/* update bc/mc sta_info */
	update_bmc_sta(padapter);

}