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
struct drvint_cmd_parm {int /*<<< orphan*/ * pbuf; scalar_t__ sz; int /*<<< orphan*/  i_cid; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  WDG_WK_CID ; 
 int /*<<< orphan*/  _DRV_INT_CMD_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct drvint_cmd_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd_ex (struct cmd_priv*,struct cmd_obj*) ; 

void r8712_wdg_wk_cmd(struct _adapter *padapter)
{
	struct cmd_obj *ph2c;
	struct drvint_cmd_parm  *pdrvintcmd_param;
	struct cmd_priv	*pcmdpriv = &padapter->cmdpriv;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		return;
	pdrvintcmd_param = kmalloc(sizeof(*pdrvintcmd_param), GFP_ATOMIC);
	if (!pdrvintcmd_param) {
		kfree(ph2c);
		return;
	}
	pdrvintcmd_param->i_cid = WDG_WK_CID;
	pdrvintcmd_param->sz = 0;
	pdrvintcmd_param->pbuf = NULL;
	init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvintcmd_param, _DRV_INT_CMD_);
	r8712_enqueue_cmd_ex(pcmdpriv, ph2c);
}