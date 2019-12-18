#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct drvextra_cmd_parm {scalar_t__ ec_id; } ;
struct cmd_priv {int /*<<< orphan*/  cmdthd_running; TYPE_3__* padapter; } ;
struct cmd_obj {scalar_t__ cmdcode; scalar_t__ parmbuf; } ;
struct TYPE_5__ {int /*<<< orphan*/  usbss_enable; } ;
struct TYPE_4__ {scalar_t__ bHWPwrPindetect; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_init_completed; TYPE_2__ registrypriv; TYPE_1__ pwrctrlpriv; } ;

/* Variables and functions */
 scalar_t__ POWER_SAVING_CTRL_WK_CID ; 
 int _FAIL ; 
 int _SUCCESS ; 
 scalar_t__ _SetChannelPlan_CMD_ ; 
 scalar_t__ _Set_Drv_Extra_CMD_ ; 

__attribute__((used)) static int rtw_cmd_filter(struct cmd_priv *pcmdpriv, struct cmd_obj *cmd_obj)
{
	u8 bAllow = false; /* set to true to allow enqueuing cmd when hw_init_completed is false */

	/* To decide allow or not */
	if ((pcmdpriv->padapter->pwrctrlpriv.bHWPwrPindetect) &&
	    (!pcmdpriv->padapter->registrypriv.usbss_enable)) {
		if (cmd_obj->cmdcode == _Set_Drv_Extra_CMD_) {
			struct drvextra_cmd_parm	*pdrvextra_cmd_parm = (struct drvextra_cmd_parm	*)cmd_obj->parmbuf;

			if (pdrvextra_cmd_parm->ec_id == POWER_SAVING_CTRL_WK_CID)
				bAllow = true;
		}
	}

	if (cmd_obj->cmdcode == _SetChannelPlan_CMD_)
		bAllow = true;

	if ((!pcmdpriv->padapter->hw_init_completed && !bAllow) ||
	    !pcmdpriv->cmdthd_running)	/* com_thread not running */
		return _FAIL;
	return _SUCCESS;
}