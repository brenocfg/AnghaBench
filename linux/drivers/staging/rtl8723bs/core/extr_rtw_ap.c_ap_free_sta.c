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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int agg_enable_bitmap; int candidate_tid_bitmap; } ;
struct sta_info {int /*<<< orphan*/  hwaddr; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_1__ htpriv; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _FW_LINKED ; 
 int bss_cap_update_on_sta_leave (struct adapter*,struct sta_info*) ; 
 int /*<<< orphan*/  issue_deauth (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_del_sta_event (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_cfg80211_indicate_sta_disassoc (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_clearstakey_cmd (struct adapter*,struct sta_info*,int) ; 
 int /*<<< orphan*/  rtw_free_stainfo (struct adapter*,struct sta_info*) ; 
 int /*<<< orphan*/  send_delba (struct adapter*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

u8 ap_free_sta(
	struct adapter *padapter,
	struct sta_info *psta,
	bool active,
	u16 reason
)
{
	u8 beacon_updated = false;

	if (!psta)
		return beacon_updated;

	if (active) {
		/* tear down Rx AMPDU */
		send_delba(padapter, 0, psta->hwaddr);/*  recipient */

		/* tear down TX AMPDU */
		send_delba(padapter, 1, psta->hwaddr);/*  // originator */

		issue_deauth(padapter, psta->hwaddr, reason);
	}

	psta->htpriv.agg_enable_bitmap = 0x0;/* reset */
	psta->htpriv.candidate_tid_bitmap = 0x0;/* reset */

	/* report_del_sta_event(padapter, psta->hwaddr, reason); */

	/* clear cam entry / key */
	rtw_clearstakey_cmd(padapter, psta, true);

	spin_lock_bh(&psta->lock);
	psta->state &= ~_FW_LINKED;
	spin_unlock_bh(&psta->lock);

	rtw_cfg80211_indicate_sta_disassoc(padapter, psta->hwaddr, reason);

	report_del_sta_event(padapter, psta->hwaddr, reason);

	beacon_updated = bss_cap_update_on_sta_leave(padapter, psta);

	rtw_free_stainfo(padapter, psta);

	return beacon_updated;
}