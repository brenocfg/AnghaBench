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
struct disconnect_parm {int dummy; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _DisConnect_CMD_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct disconnect_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 

void r8712_disassoc_cmd(struct _adapter *padapter) /* for sta_mode */
{
	struct cmd_obj *pdisconnect_cmd;
	struct disconnect_parm *pdisconnect;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;

	pdisconnect_cmd = kmalloc(sizeof(*pdisconnect_cmd), GFP_ATOMIC);
	if (!pdisconnect_cmd)
		return;
	pdisconnect = kmalloc(sizeof(*pdisconnect), GFP_ATOMIC);
	if (!pdisconnect) {
		kfree(pdisconnect_cmd);
		return;
	}
	init_h2fwcmd_w_parm_no_rsp(pdisconnect_cmd, pdisconnect,
				   _DisConnect_CMD_);
	r8712_enqueue_cmd(pcmdpriv, pdisconnect_cmd);
}