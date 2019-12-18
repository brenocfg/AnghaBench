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
struct mlme_ext_info {int state; } ;
struct mlme_ext_priv {int /*<<< orphan*/  link_timer; struct mlme_ext_info mlmext_info; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  REASSOC_TO ; 
 int WIFI_FW_ASSOC_STATE ; 
 int WIFI_FW_AUTH_NULL ; 
 int WIFI_FW_AUTH_STATE ; 
 int WIFI_FW_AUTH_SUCCESS ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  issue_assocreq (struct adapter*) ; 
 int /*<<< orphan*/  set_link_timer (struct mlme_ext_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_clnt_assoc(struct adapter *padapter)
{
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;

	del_timer_sync(&pmlmeext->link_timer);

	pmlmeinfo->state &= (~(WIFI_FW_AUTH_NULL | WIFI_FW_AUTH_STATE));
	pmlmeinfo->state |= (WIFI_FW_AUTH_SUCCESS | WIFI_FW_ASSOC_STATE);

	issue_assocreq(padapter);

	set_link_timer(pmlmeext, REASSOC_TO);
}