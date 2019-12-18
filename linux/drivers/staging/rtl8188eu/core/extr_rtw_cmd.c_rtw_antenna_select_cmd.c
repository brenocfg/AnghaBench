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
struct drvextra_cmd_parm {int /*<<< orphan*/ * pbuf; scalar_t__ type_size; int /*<<< orphan*/  ec_id; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct adapter {struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ANT_SELECT_WK_CID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HAL_DEF_IS_SUPPORT_ANT_DIV ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _Set_Drv_Extra_CMD_ ; 
 int /*<<< orphan*/  antenna_select_wk_hdl (struct adapter*,scalar_t__) ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct drvextra_cmd_parm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,scalar_t__*) ; 

u8 rtw_antenna_select_cmd(struct adapter *padapter, u8 antenna, u8 enqueue)
{
	struct cmd_obj		*ph2c;
	struct drvextra_cmd_parm	*pdrvextra_cmd_parm;
	struct cmd_priv	*pcmdpriv = &padapter->cmdpriv;
	u8	support_ant_div;
	u8	res = _SUCCESS;

	rtw_hal_get_def_var(padapter, HAL_DEF_IS_SUPPORT_ANT_DIV, &support_ant_div);
	if (!support_ant_div)
		return res;

	if (enqueue) {
		ph2c = kzalloc(sizeof(*ph2c), GFP_KERNEL);
		if (!ph2c) {
			res = _FAIL;
			goto exit;
		}

		pdrvextra_cmd_parm = kzalloc(sizeof(*pdrvextra_cmd_parm), GFP_KERNEL);
		if (!pdrvextra_cmd_parm) {
			kfree(ph2c);
			res = _FAIL;
			goto exit;
		}

		pdrvextra_cmd_parm->ec_id = ANT_SELECT_WK_CID;
		pdrvextra_cmd_parm->type_size = antenna;
		pdrvextra_cmd_parm->pbuf = NULL;
		init_h2fwcmd_w_parm_no_rsp(ph2c, pdrvextra_cmd_parm, _Set_Drv_Extra_CMD_);

		res = rtw_enqueue_cmd(pcmdpriv, ph2c);
	} else {
		antenna_select_wk_hdl(padapter, antenna);
	}
exit:

	return res;
}