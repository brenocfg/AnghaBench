#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mlme_ext_info {int /*<<< orphan*/  state; } ;
struct mlme_ext_priv {int /*<<< orphan*/  link_timer; int /*<<< orphan*/  cur_bwmode; int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_channel; struct mlme_ext_info mlmext_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  wireless_mode; } ;
struct adapter {TYPE_1__ registrypriv; struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_PRIME_CHNL_OFFSET_DONT_CARE ; 
 int /*<<< orphan*/  HT_CHANNEL_WIDTH_20 ; 
 int /*<<< orphan*/  HW_VAR_BSSID ; 
 int /*<<< orphan*/  HW_VAR_MLME_DISCONNECT ; 
 int /*<<< orphan*/  Set_MSR (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_FW_NULL_STATE ; 
 int /*<<< orphan*/  _HW_STATE_STATION_ ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_all_cam_entry (struct adapter*) ; 
 scalar_t__ is_IBSS_empty (struct adapter*) ; 
 scalar_t__ is_client_associated_to_ap (struct adapter*) ; 
 int /*<<< orphan*/ * null_addr ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_channel_bwmode (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_tx_basic_rate (struct adapter*,int /*<<< orphan*/ ) ; 

void mlmeext_sta_del_event_callback(struct adapter *padapter)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	if (is_client_associated_to_ap(padapter) || is_IBSS_empty(padapter)) {
		rtw_hal_set_hwreg(padapter, HW_VAR_MLME_DISCONNECT, NULL);
		rtw_hal_set_hwreg(padapter, HW_VAR_BSSID, null_addr);

		/* restore to initial setting. */
		update_tx_basic_rate(padapter, padapter->registrypriv.wireless_mode);

		/* switch to the 20M Hz mode after disconnect */
		pmlmeext->cur_bwmode = HT_CHANNEL_WIDTH_20;
		pmlmeext->cur_ch_offset = HAL_PRIME_CHNL_OFFSET_DONT_CARE;

		/* SelectChannel(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset); */
		set_channel_bwmode(padapter, pmlmeext->cur_channel, pmlmeext->cur_ch_offset, pmlmeext->cur_bwmode);

		flush_all_cam_entry(padapter);

		pmlmeinfo->state = WIFI_FW_NULL_STATE;

		/* set MSR to no link state -> infra. mode */
		Set_MSR(padapter, _HW_STATE_STATION_);

		del_timer_sync(&pmlmeext->link_timer);
	}
}