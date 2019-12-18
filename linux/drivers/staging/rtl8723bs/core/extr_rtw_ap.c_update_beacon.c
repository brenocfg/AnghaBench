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
typedef  int u8 ;
struct mlme_priv {int update_bcn; int /*<<< orphan*/  bcn_update_lock; } ;
struct mlme_ext_priv {int /*<<< orphan*/  bstart_bss; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
#define  _ERPINFO_IE_ 133 
#define  _HT_ADD_INFO_IE_ 132 
#define  _HT_CAPABILITY_IE_ 131 
#define  _RSN_IE_2_ 130 
#define  _TIM_IE_ 129 
#define  _VENDOR_SPECIFIC_IE_ 128 
 int /*<<< orphan*/  set_tx_beacon_cmd (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_BCNTIM (struct adapter*) ; 
 int /*<<< orphan*/  update_bcn_erpinfo_ie (struct adapter*) ; 
 int /*<<< orphan*/  update_bcn_fixed_ie (struct adapter*) ; 
 int /*<<< orphan*/  update_bcn_htcap_ie (struct adapter*) ; 
 int /*<<< orphan*/  update_bcn_htinfo_ie (struct adapter*) ; 
 int /*<<< orphan*/  update_bcn_rsn_ie (struct adapter*) ; 
 int /*<<< orphan*/  update_bcn_vendor_spec_ie (struct adapter*,int*) ; 

void update_beacon(struct adapter *padapter, u8 ie_id, u8 *oui, u8 tx)
{
	struct mlme_priv *pmlmepriv;
	struct mlme_ext_priv *pmlmeext;
	/* struct mlme_ext_info *pmlmeinfo; */

	/* DBG_871X("%s\n", __func__); */

	if (!padapter)
		return;

	pmlmepriv = &(padapter->mlmepriv);
	pmlmeext = &(padapter->mlmeextpriv);
	/* pmlmeinfo = &(pmlmeext->mlmext_info); */

	if (!pmlmeext->bstart_bss)
		return;

	spin_lock_bh(&pmlmepriv->bcn_update_lock);

	switch (ie_id) {
	case 0xFF:

		update_bcn_fixed_ie(padapter);/* 8: TimeStamp, 2: Beacon Interval 2:Capability */

		break;

	case _TIM_IE_:

		update_BCNTIM(padapter);

		break;

	case _ERPINFO_IE_:

		update_bcn_erpinfo_ie(padapter);

		break;

	case _HT_CAPABILITY_IE_:

		update_bcn_htcap_ie(padapter);

		break;

	case _RSN_IE_2_:

		update_bcn_rsn_ie(padapter);

		break;

	case _HT_ADD_INFO_IE_:

		update_bcn_htinfo_ie(padapter);

		break;

	case _VENDOR_SPECIFIC_IE_:

		update_bcn_vendor_spec_ie(padapter, oui);

		break;

	default:
		break;
	}

	pmlmepriv->update_bcn = true;

	spin_unlock_bh(&pmlmepriv->bcn_update_lock);

#ifndef CONFIG_INTERRUPT_BASED_TXBCN
	if (tx) {
		/* send_beacon(padapter);//send_beacon must execute on TSR level */
		set_tx_beacon_cmd(padapter);
	}
#endif /* CONFIG_INTERRUPT_BASED_TXBCN */
}