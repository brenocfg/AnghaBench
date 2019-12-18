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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int /*<<< orphan*/  hwaddr; } ;
struct set_stakey_rsp {int dummy; } ;
struct set_stakey_parm {int rspsz; int /*<<< orphan*/  id; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  addr; int /*<<< orphan*/ * rsp; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int rspsz; int /*<<< orphan*/  id; int /*<<< orphan*/  algorithm; int /*<<< orphan*/  addr; int /*<<< orphan*/ * rsp; } ;
struct adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _NO_PRIVACY_ ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _SetStaKey_CMD_ ; 
 int /*<<< orphan*/  clear_cam_entry (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct set_stakey_parm*,struct set_stakey_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct set_stakey_parm*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct set_stakey_parm*) ; 

u8 rtw_clearstakey_cmd(struct adapter *padapter, u8 *psta, u8 entry, u8 enqueue)
{
	struct cmd_obj *ph2c;
	struct set_stakey_parm	*psetstakey_para;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;
	struct set_stakey_rsp *psetstakey_rsp = NULL;
	struct sta_info *sta = (struct sta_info *)psta;
	u8	res = _SUCCESS;

	if (!enqueue) {
		clear_cam_entry(padapter, entry);
	} else {
		ph2c = kzalloc(sizeof(*ph2c), GFP_ATOMIC);
		if (!ph2c) {
			res = _FAIL;
			goto exit;
		}

		psetstakey_para = kzalloc(sizeof(*psetstakey_para), GFP_ATOMIC);
		if (!psetstakey_para) {
			kfree(ph2c);
			res = _FAIL;
			goto exit;
		}

		psetstakey_rsp = kzalloc(sizeof(*psetstakey_rsp), GFP_ATOMIC);
		if (!psetstakey_rsp) {
			kfree(ph2c);
			kfree(psetstakey_para);
			res = _FAIL;
			goto exit;
		}

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetstakey_para, _SetStaKey_CMD_);
		ph2c->rsp = (u8 *)psetstakey_rsp;
		ph2c->rspsz = sizeof(struct set_stakey_rsp);

		ether_addr_copy(psetstakey_para->addr, sta->hwaddr);

		psetstakey_para->algorithm = _NO_PRIVACY_;

		psetstakey_para->id = entry;

		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	}
exit:

	return res;
}