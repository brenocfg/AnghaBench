#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int ht_option; int ampdu_enable; int sgi; int agg_enable_bitmap; int candidate_tid_bitmap; int /*<<< orphan*/  ch_offset; int /*<<< orphan*/  bwmode; } ;
struct sta_info {int qos_option; int /*<<< orphan*/  state; TYPE_2__ htpriv; } ;
struct TYPE_6__ {scalar_t__ qos_option; } ;
struct TYPE_4__ {int ampdu_enable; scalar_t__ ht_option; } ;
struct mlme_priv {TYPE_3__ qospriv; TYPE_1__ htpriv; } ;
struct mlme_ext_info {int /*<<< orphan*/  HT_caps; } ;
struct mlme_ext_priv {int /*<<< orphan*/  cur_ch_offset; int /*<<< orphan*/  cur_bwmode; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCS_update (struct adapter*,struct sta_info*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ support_short_GI (struct adapter*,int /*<<< orphan*/ *) ; 

void update_sta_info(struct adapter *padapter, struct sta_info *psta)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	/* ERP */
	VCS_update(padapter, psta);

	/* HT */
	if (pmlmepriv->htpriv.ht_option) {
		psta->htpriv.ht_option = true;

		psta->htpriv.ampdu_enable = pmlmepriv->htpriv.ampdu_enable;

		if (support_short_GI(padapter, &pmlmeinfo->HT_caps))
			psta->htpriv.sgi = true;

		psta->qos_option = true;
	} else {
		psta->htpriv.ht_option = false;

		psta->htpriv.ampdu_enable = false;

		psta->htpriv.sgi = false;
		psta->qos_option = false;
	}
	psta->htpriv.bwmode = pmlmeext->cur_bwmode;
	psta->htpriv.ch_offset = pmlmeext->cur_ch_offset;

	psta->htpriv.agg_enable_bitmap = 0x0;/* reset */
	psta->htpriv.candidate_tid_bitmap = 0x0;/* reset */

	/* QoS */
	if (pmlmepriv->qospriv.qos_option)
		psta->qos_option = true;

	psta->state = _FW_LINKED;
}