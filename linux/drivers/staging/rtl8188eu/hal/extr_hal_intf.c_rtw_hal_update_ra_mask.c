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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct sta_priv {struct sta_info** sta_aid; } ;
struct sta_info {int dummy; } ;
struct mlme_priv {int dummy; } ;
struct adapter {struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  UpdateHalRAMask8188EUsb (struct adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_AP_STATE ; 
 int /*<<< orphan*/  add_RATid (struct adapter*,struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

void rtw_hal_update_ra_mask(struct adapter *adapt, u32 mac_id, u8 rssi_level)
{
	struct mlme_priv *pmlmepriv = &adapt->mlmepriv;

	if (check_fwstate(pmlmepriv, WIFI_AP_STATE)) {
#ifdef CONFIG_88EU_AP_MODE
		struct sta_info *psta = NULL;
		struct sta_priv *pstapriv = &adapt->stapriv;

		if (mac_id - 1 > 0)
			psta = pstapriv->sta_aid[mac_id - 2];
		if (psta)
			add_RATid(adapt, psta, 0);/* todo: based on rssi_level*/
#endif
	} else {
		UpdateHalRAMask8188EUsb(adapt, mac_id, rssi_level);
	}
}