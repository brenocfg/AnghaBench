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
struct ht_priv {int /*<<< orphan*/  ht_option; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct mlme_ext_info {int HT_info_enable; int /*<<< orphan*/  HT_info; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_priv mlmepriv; struct mlme_ext_priv mlmeextpriv; } ;
struct HT_info_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void HT_info_handler(struct adapter *padapter, struct ndis_802_11_var_ie *pIE)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv *phtpriv = &pmlmepriv->htpriv;

	if (!pIE)
		return;

	if (!phtpriv->ht_option)
		return;

	if (pIE->Length > sizeof(struct HT_info_element))
		return;

	pmlmeinfo->HT_info_enable = 1;
	memcpy(&pmlmeinfo->HT_info, pIE->data, pIE->Length);
}