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
struct ndis_802_11_var_ie {int Length; int /*<<< orphan*/  data; } ;
struct mlme_ext_info {int ERP_enable; int /*<<< orphan*/  ERP_IE; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void ERP_IE_handler(struct adapter *padapter, struct ndis_802_11_var_ie *pIE)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	if (pIE->Length > 1)
		return;

	pmlmeinfo->ERP_enable = 1;
	memcpy(&pmlmeinfo->ERP_IE, pIE->data, pIE->Length);
}