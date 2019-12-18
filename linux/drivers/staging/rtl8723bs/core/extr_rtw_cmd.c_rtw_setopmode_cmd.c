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
typedef  scalar_t__ u8 ;
struct setopmode_parm {scalar_t__ mode; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct adapter {struct cmd_priv cmdpriv; } ;
typedef  enum NDIS_802_11_NETWORK_INFRASTRUCTURE { ____Placeholder_NDIS_802_11_NETWORK_INFRASTRUCTURE } NDIS_802_11_NETWORK_INFRASTRUCTURE ;

/* Variables and functions */
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _SetOpMode_CMD_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct setopmode_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct setopmode_parm*) ; 
 scalar_t__ rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 void* rtw_zmalloc (int) ; 
 int /*<<< orphan*/  setopmode_hdl (struct adapter*,scalar_t__*) ; 

u8 rtw_setopmode_cmd(struct adapter  *padapter, enum NDIS_802_11_NETWORK_INFRASTRUCTURE networktype, bool enqueue)
{
	struct	cmd_obj *ph2c;
	struct	setopmode_parm *psetop;

	struct	cmd_priv   *pcmdpriv = &padapter->cmdpriv;
	u8 res = _SUCCESS;

	psetop = rtw_zmalloc(sizeof(struct setopmode_parm));

	if (psetop == NULL) {
		res = _FAIL;
		goto exit;
	}
	psetop->mode = (u8)networktype;

	if (enqueue) {
		ph2c = rtw_zmalloc(sizeof(struct cmd_obj));
		if (ph2c == NULL) {
			kfree(psetop);
			res = _FAIL;
			goto exit;
		}

		init_h2fwcmd_w_parm_no_rsp(ph2c, psetop, _SetOpMode_CMD_);
		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	} else {
		setopmode_hdl(padapter, (u8 *)psetop);
		kfree(psetop);
	}
exit:
	return res;
}