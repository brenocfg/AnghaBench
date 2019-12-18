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
struct ndis_802_11_var_ie {scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ qos_option; } ;
struct mlme_priv {TYPE_1__ qospriv; } ;
struct mlme_ext_info {int WMM_enable; int /*<<< orphan*/  WMM_param; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;
struct WMM_para_element {int dummy; } ;

/* Variables and functions */
 int _FAIL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__,int) ; 

int WMM_param_handler(struct adapter *padapter, struct ndis_802_11_var_ie *pIE)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	if (pmlmepriv->qospriv.qos_option == 0) {
		pmlmeinfo->WMM_enable = 0;
		return _FAIL;
	}

	pmlmeinfo->WMM_enable = 1;
	memcpy(&pmlmeinfo->WMM_param, pIE->data + 6, sizeof(struct WMM_para_element));
	return true;
}