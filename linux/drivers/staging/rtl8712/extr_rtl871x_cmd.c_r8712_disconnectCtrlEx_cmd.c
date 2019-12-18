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
typedef  scalar_t__ u32 ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct _adapter {struct cmd_priv cmdpriv; } ;
struct DisconnectCtrlEx_param {unsigned char EnableDrvCtrl; unsigned char TryPktCnt; unsigned char TryPktInterval; unsigned int FirstStageTO; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  _DisconnectCtrlEx ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct DisconnectCtrlEx_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 struct cmd_obj* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct DisconnectCtrlEx_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r8712_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 

void r8712_disconnectCtrlEx_cmd(struct _adapter *adapter, u32 enableDrvCtrl,
			u32 tryPktCnt, u32 tryPktInterval, u32 firstStageTO)
{
	struct cmd_obj *ph2c;
	struct DisconnectCtrlEx_param *param;
	struct cmd_priv *pcmdpriv = &adapter->cmdpriv;

	ph2c = kmalloc(sizeof(*ph2c), GFP_ATOMIC);
	if (!ph2c)
		return;
	param = kzalloc(sizeof(*param), GFP_ATOMIC);
	if (!param) {
		kfree(ph2c);
		return;
	}

	param->EnableDrvCtrl = (unsigned char)enableDrvCtrl;
	param->TryPktCnt = (unsigned char)tryPktCnt;
	param->TryPktInterval = (unsigned char)tryPktInterval;
	param->FirstStageTO = (unsigned int)firstStageTO;

	init_h2fwcmd_w_parm_no_rsp(ph2c, param,
				GEN_CMD_CODE(_DisconnectCtrlEx));
	r8712_enqueue_cmd(pcmdpriv, ph2c);
}