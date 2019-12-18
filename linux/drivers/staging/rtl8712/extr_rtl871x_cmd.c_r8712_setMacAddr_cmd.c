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
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;
struct SetMacAddr_param {int /*<<< orphan*/  MacAddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _SetMacAddress_CMD_ ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct SetMacAddr_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 

void r8712_setMacAddr_cmd(struct _adapter *padapter, u8 *mac_addr)
{
	struct cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	struct cmd_obj *ph2c;
	struct SetMacAddr_param	*psetMacAddr_para;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		return;
	psetMacAddr_para = kmalloc(sizeof(*psetMacAddr_para), GFP_ATOMIC);
	if (!psetMacAddr_para) {
		kfree(ph2c);
		return;
	}
	init_h2fwcmd_w_parm_no_rsp(ph2c, psetMacAddr_para,
				   _SetMacAddress_CMD_);
	ether_addr_copy(psetMacAddr_para->MacAddr, mac_addr);
	r8712_enqueue_cmd(pcmdpriv, ph2c);
}