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
struct TYPE_2__ {int /*<<< orphan*/  MacAddress; } ;
struct wlan_network {TYPE_1__ network; } ;
struct sta_info {int dummy; } ;
struct mp_priv {int /*<<< orphan*/  prev_fw_state; } ;
struct mlme_priv {int /*<<< orphan*/  lock; int /*<<< orphan*/  fw_state; struct wlan_network cur_network; } ;
struct _adapter {int /*<<< orphan*/  stapriv; struct mlme_priv mlmepriv; struct mp_priv mppriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct wlan_network*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8712_free_stainfo (struct _adapter*,struct sta_info*) ; 
 struct sta_info* r8712_get_stainfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_os_indicate_disconnect (struct _adapter*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mp_stop_test(struct _adapter *padapter)
{
	struct mp_priv *pmppriv = &padapter->mppriv;
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct wlan_network *tgt_network = &pmlmepriv->cur_network;
	struct sta_info *psta;
	unsigned long irqL;

	spin_lock_irqsave(&pmlmepriv->lock, irqL);
	if (!check_fwstate(pmlmepriv, WIFI_MP_STATE))
		goto end_of_mp_stop_test;
	/* 3 1. disconnect pseudo AdHoc */
	r8712_os_indicate_disconnect(padapter);
	/* 3 2. clear psta used in mp test mode. */
	psta = r8712_get_stainfo(&padapter->stapriv,
				 tgt_network->network.MacAddress);
	if (psta)
		r8712_free_stainfo(padapter, psta);
	/* 3 3. return to normal state (default:station mode) */
	pmlmepriv->fw_state = pmppriv->prev_fw_state; /* WIFI_STATION_STATE;*/
	/*flush the cur_network*/
	memset(tgt_network, 0, sizeof(struct wlan_network));
end_of_mp_stop_test:
	spin_unlock_irqrestore(&pmlmepriv->lock, irqL);
	return _SUCCESS;
}