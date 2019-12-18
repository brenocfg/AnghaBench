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
struct sta_info {int state; size_t mac_id; } ;
struct mlme_ext_info {TYPE_1__* FW_sta_info; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;
struct TYPE_2__ {struct sta_info* psta; } ;

/* Variables and functions */
 int _FW_LINKED ; 
 int /*<<< orphan*/  add_RATid (struct adapter*,struct sta_info*,int /*<<< orphan*/ ) ; 

void ap_sta_info_defer_update(struct adapter *padapter, struct sta_info *psta)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);

	if (psta->state & _FW_LINKED) {
		pmlmeinfo->FW_sta_info[psta->mac_id].psta = psta;

		/* add ratid */
		add_RATid(padapter, psta, 0);/* DM_RATR_STA_INIT */
	}
}