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
struct wlan_acl_pool {int /*<<< orphan*/  acl_node_q; } ;
struct sta_priv {struct wlan_acl_pool acl_list; } ;
struct mlme_priv {int /*<<< orphan*/  bcn_update_lock; } ;
struct adapter {struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  start_ap_mode (struct adapter*) ; 

void init_mlme_ap_info(struct adapter *padapter)
{
	struct mlme_priv *pmlmepriv = &padapter->mlmepriv;
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	spin_lock_init(&pmlmepriv->bcn_update_lock);

	/* for ACL */
	_rtw_init_queue(&pacl_list->acl_node_q);

	/* pmlmeext->bstart_bss = false; */

	start_ap_mode(padapter);
}