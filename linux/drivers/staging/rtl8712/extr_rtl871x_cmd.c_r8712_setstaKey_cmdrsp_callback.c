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
struct sta_priv {int dummy; } ;
struct sta_info {int /*<<< orphan*/  mac_id; int /*<<< orphan*/  aid; } ;
struct set_stakey_rsp {int /*<<< orphan*/  keyid; int /*<<< orphan*/  addr; } ;
struct cmd_obj {scalar_t__ rsp; } ;
struct _adapter {struct sta_priv stapriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_free_cmd_obj (struct cmd_obj*) ; 
 struct sta_info* r8712_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 

void r8712_setstaKey_cmdrsp_callback(struct _adapter *padapter,
				     struct cmd_obj *pcmd)
{
	struct sta_priv *pstapriv = &padapter->stapriv;
	struct set_stakey_rsp *psetstakey_rsp = (struct set_stakey_rsp *)
						(pcmd->rsp);
	struct sta_info *psta = r8712_get_stainfo(pstapriv,
						  psetstakey_rsp->addr);

	if (!psta)
		goto exit;
	psta->aid = psta->mac_id = psetstakey_rsp->keyid; /*CAM_ID(CAM_ENTRY)*/
exit:
	r8712_free_cmd_obj(pcmd);
}