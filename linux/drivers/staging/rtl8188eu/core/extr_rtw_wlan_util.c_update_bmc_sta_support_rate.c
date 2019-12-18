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
typedef  size_t u32 ;
struct mlme_ext_info {TYPE_1__* FW_sta_info; } ;
struct mlme_ext_priv {int cur_wireless_mode; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_2__ {int /*<<< orphan*/  SupportedRates; } ;

/* Variables and functions */
 int WIRELESS_11B ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_basic_rate_cck ; 
 int /*<<< orphan*/  rtw_basic_rate_ofdm ; 

void update_bmc_sta_support_rate(struct adapter *padapter, u32 mac_id)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	if (pmlmeext->cur_wireless_mode & WIRELESS_11B) {
		/*  Only B, B/G, and B/G/N AP could use CCK rate */
		memcpy((pmlmeinfo->FW_sta_info[mac_id].SupportedRates), rtw_basic_rate_cck, 4);
	} else {
		memcpy((pmlmeinfo->FW_sta_info[mac_id].SupportedRates), rtw_basic_rate_ofdm, 3);
	}
}