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
struct timer_list {int dummy; } ;
struct mlme_priv {int /*<<< orphan*/  lock; } ;
struct adapter {struct mlme_priv mlmepriv; } ;
struct TYPE_2__ {int /*<<< orphan*/  sa_query_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_871X (char*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 struct adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 TYPE_1__ mlmeextpriv ; 
 struct adapter* padapter ; 
 int /*<<< orphan*/  rtw_disassoc_cmd (struct adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_free_assoc_resources (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_indicate_disconnect (struct adapter*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void sa_query_timer_hdl(struct timer_list *t)
{
	struct adapter *padapter =
		from_timer(padapter, t, mlmeextpriv.sa_query_timer);
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	/* disconnect */
	spin_lock_bh(&pmlmepriv->lock);

	if (check_fwstate(pmlmepriv, _FW_LINKED)) {
		rtw_disassoc_cmd(padapter, 0, true);
		rtw_indicate_disconnect(padapter);
		rtw_free_assoc_resources(padapter, 1);
	}

	spin_unlock_bh(&pmlmepriv->lock);
	DBG_871X("SA query timeout disconnect\n");
}