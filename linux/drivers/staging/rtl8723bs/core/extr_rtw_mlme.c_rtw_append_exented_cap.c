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
typedef  int uint ;
typedef  int /*<<< orphan*/  u8 ;
struct ht_priv {scalar_t__ bss_coexist; } ;
struct mlme_priv {struct ht_priv htpriv; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EID_EXTCapability ; 
 int /*<<< orphan*/  SET_EXT_CAPABILITY_ELE_BSS_COEXIST (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * rtw_set_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

void rtw_append_exented_cap(struct adapter *padapter, u8 *out_ie, uint *pout_len)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct ht_priv 	*phtpriv = &pmlmepriv->htpriv;
	u8 cap_content[8] = {0};
	u8 *pframe;


	if (phtpriv->bss_coexist) {
		SET_EXT_CAPABILITY_ELE_BSS_COEXIST(cap_content, 1);
	}

	pframe = rtw_set_ie(out_ie + *pout_len, EID_EXTCapability, 8, cap_content, pout_len);
}