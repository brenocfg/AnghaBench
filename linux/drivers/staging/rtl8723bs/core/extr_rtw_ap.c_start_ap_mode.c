#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  queue; } ;
struct wlan_acl_pool {TYPE_2__* aclnode; scalar_t__ mode; scalar_t__ num; TYPE_1__ acl_node_q; } ;
struct sta_priv {int /*<<< orphan*/ ** sta_aid; struct wlan_acl_pool acl_list; } ;
struct mlme_priv {int update_bcn; int olbc; int olbc_ht; int /*<<< orphan*/ * p2p_probe_resp_ie; int /*<<< orphan*/ * p2p_beacon_ie; int /*<<< orphan*/ * wps_assoc_resp_ie; int /*<<< orphan*/ * wps_probe_resp_ie; int /*<<< orphan*/ * wps_beacon_ie; scalar_t__ ht_op_mode; scalar_t__ num_sta_ht_20mhz; scalar_t__ num_sta_no_ht; scalar_t__ num_sta_ht_no_gf; scalar_t__ num_sta_no_short_preamble; scalar_t__ num_sta_no_short_slot_time; scalar_t__ num_sta_non_erp; } ;
struct mlme_ext_priv {int bstart_bss; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct sta_priv stapriv; struct mlme_priv mlmepriv; } ;
struct TYPE_4__ {int valid; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_ACL ; 
 int NUM_STA ; 

void start_ap_mode(struct adapter *padapter)
{
	int i;
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct wlan_acl_pool *pacl_list = &pstapriv->acl_list;

	pmlmepriv->update_bcn = false;

	/* init_mlme_ap_info(padapter); */
	pmlmeext->bstart_bss = false;

	pmlmepriv->num_sta_non_erp = 0;

	pmlmepriv->num_sta_no_short_slot_time = 0;

	pmlmepriv->num_sta_no_short_preamble = 0;

	pmlmepriv->num_sta_ht_no_gf = 0;
	pmlmepriv->num_sta_no_ht = 0;
	pmlmepriv->num_sta_ht_20mhz = 0;

	pmlmepriv->olbc = false;

	pmlmepriv->olbc_ht = false;

	pmlmepriv->ht_op_mode = 0;

	for (i = 0; i < NUM_STA; i++)
		pstapriv->sta_aid[i] = NULL;

	pmlmepriv->wps_beacon_ie = NULL;
	pmlmepriv->wps_probe_resp_ie = NULL;
	pmlmepriv->wps_assoc_resp_ie = NULL;

	pmlmepriv->p2p_beacon_ie = NULL;
	pmlmepriv->p2p_probe_resp_ie = NULL;

	/* for ACL */
	INIT_LIST_HEAD(&(pacl_list->acl_node_q.queue));
	pacl_list->num = 0;
	pacl_list->mode = 0;
	for (i = 0; i < NUM_ACL; i++) {
		INIT_LIST_HEAD(&pacl_list->aclnode[i].list);
		pacl_list->aclnode[i].valid = false;
	}
}