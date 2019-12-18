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
struct sta_info {int dummy; } ;
struct mlme_priv {int update_bcn; } ;
struct mlme_ext_info {int /*<<< orphan*/  state; } ;
struct mlme_ext_priv {int bstart_bss; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _HW_STATE_NOLINK_ ; 
 int /*<<< orphan*/  rtw_free_all_stainfo (struct adapter*) ; 
 int /*<<< orphan*/  rtw_free_stainfo (struct adapter*,struct sta_info*) ; 
 struct sta_info* rtw_get_bcmc_stainfo (struct adapter*) ; 
 int /*<<< orphan*/  rtw_sta_flush (struct adapter*) ; 

void free_mlme_ap_info(struct adapter *padapter)
{
	struct sta_info *psta = NULL;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	/* stop_ap_mode(padapter); */

	pmlmepriv->update_bcn = false;
	pmlmeext->bstart_bss = false;

	rtw_sta_flush(padapter);

	pmlmeinfo->state = _HW_STATE_NOLINK_;

	/* free_assoc_sta_resources */
	rtw_free_all_stainfo(padapter);

	/* free bc/mc sta_info */
	psta = rtw_get_bcmc_stainfo(padapter);
	rtw_free_stainfo(padapter, psta);
}