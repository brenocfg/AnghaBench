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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct wlan_bssid_ex {int* SupportedRates; } ;
struct TYPE_5__ {int /*<<< orphan*/  supp_mcs_set; } ;
struct TYPE_6__ {TYPE_2__ ht_cap; } ;
struct sta_info {scalar_t__ bw_mode; TYPE_3__ htpriv; int /*<<< orphan*/  wireless_mode; } ;
struct TYPE_4__ {struct wlan_bssid_ex network; } ;
struct mlme_priv {TYPE_1__ cur_network; } ;
struct adapter {int /*<<< orphan*/  stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 scalar_t__ CHANNEL_WIDTH_40 ; 
 int /*<<< orphan*/  HW_VAR_RF_TYPE ; 
 scalar_t__ IsSupportedHT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bssid (struct mlme_priv*) ; 
 scalar_t__ query_ra_short_GI (struct sta_info*) ; 
 struct sta_info* rtw_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int rtw_mcs_rate (scalar_t__,int,scalar_t__,int /*<<< orphan*/ ) ; 

u16 rtw_get_cur_max_rate(struct adapter *adapter)
{
	int	i = 0;
	u16 rate = 0, max_rate = 0;
	struct mlme_priv *pmlmepriv = &adapter->mlmepriv;
	struct wlan_bssid_ex	*pcur_bss = &pmlmepriv->cur_network.network;
	struct sta_info *psta = NULL;
	u8 short_GI = 0;
	u8 rf_type = 0;

	if ((check_fwstate(pmlmepriv, _FW_LINKED) != true)
		&& (check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) != true))
		return 0;

	psta = rtw_get_stainfo(&adapter->stapriv, get_bssid(pmlmepriv));
	if (psta == NULL)
		return 0;

	short_GI = query_ra_short_GI(psta);

	if (IsSupportedHT(psta->wireless_mode)) {
		rtw_hal_get_hwreg(adapter, HW_VAR_RF_TYPE, (u8 *)(&rf_type));

		max_rate = rtw_mcs_rate(
			rf_type,
			((psta->bw_mode == CHANNEL_WIDTH_40)?1:0),
			short_GI,
			psta->htpriv.ht_cap.supp_mcs_set
		);
	} else {
		while ((pcur_bss->SupportedRates[i] != 0) && (pcur_bss->SupportedRates[i] != 0xFF)) {
			rate = pcur_bss->SupportedRates[i]&0x7F;
			if (rate > max_rate)
				max_rate = rate;
			i++;
		}

		max_rate = max_rate*10/2;
	}

	return max_rate;
}