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
typedef  int u8 ;
struct setopmode_parm {int mode; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int mode; } ;
struct adapter {struct cmd_priv cmdpriv; } ;
typedef  enum ndis_802_11_network_infra { ____Placeholder_ndis_802_11_network_infra } ndis_802_11_network_infra ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  _SetOpMode_CMD_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct setopmode_parm*,struct setopmode_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct setopmode_parm*) ; 
 struct setopmode_parm* kzalloc (int,int /*<<< orphan*/ ) ; 
 int rtw_enqueue_cmd (struct cmd_priv*,struct setopmode_parm*) ; 

u8 rtw_setopmode_cmd(struct adapter  *padapter, enum ndis_802_11_network_infra networktype)
{
	struct	cmd_obj *ph2c;
	struct	setopmode_parm *psetop;

	struct	cmd_priv   *pcmdpriv = &padapter->cmdpriv;

	ph2c = kzalloc(sizeof(*ph2c), GFP_KERNEL);
	psetop = kzalloc(sizeof(*psetop), GFP_KERNEL);
	if (!ph2c || !psetop) {
		kfree(ph2c);
		kfree(psetop);
		return false;
	}

	init_h2fwcmd_w_parm_no_rsp(ph2c, psetop, _SetOpMode_CMD_);
	psetop->mode = (u8)networktype;

	return rtw_enqueue_cmd(pcmdpriv, ph2c);
}