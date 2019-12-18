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
struct setopmode_parm {scalar_t__ mode; } ;
struct mlme_ext_info {int state; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  H2C_SUCCESS ; 
 int /*<<< orphan*/  HW_VAR_SET_OPMODE ; 
 scalar_t__ Ndis802_11APMode ; 
 scalar_t__ Ndis802_11IBSS ; 
 scalar_t__ Ndis802_11Infrastructure ; 
 int WIFI_FW_AP_STATE ; 
 int WIFI_FW_STATION_STATE ; 
 int /*<<< orphan*/  _HW_STATE_ADHOC_ ; 
 int /*<<< orphan*/  _HW_STATE_AP_ ; 
 int /*<<< orphan*/  _HW_STATE_NOLINK_ ; 
 int /*<<< orphan*/  _HW_STATE_STATION_ ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u8 setopmode_hdl(struct adapter *padapter, u8 *pbuf)
{
	u8 type;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct setopmode_parm *psetop = (struct setopmode_parm *)pbuf;

	if (psetop->mode == Ndis802_11APMode) {
		pmlmeinfo->state = WIFI_FW_AP_STATE;
		type = _HW_STATE_AP_;
	} else if (psetop->mode == Ndis802_11Infrastructure) {
		pmlmeinfo->state &= ~(BIT(0)|BIT(1));/*  clear state */
		pmlmeinfo->state |= WIFI_FW_STATION_STATE;/* set to	STATION_STATE */
		type = _HW_STATE_STATION_;
	} else if (psetop->mode == Ndis802_11IBSS) {
		type = _HW_STATE_ADHOC_;
	} else {
		type = _HW_STATE_NOLINK_;
	}

	rtw_hal_set_hwreg(padapter, HW_VAR_SET_OPMODE, (u8 *)(&type));
	/* Set_MSR(padapter, type); */

	return H2C_SUCCESS;
}