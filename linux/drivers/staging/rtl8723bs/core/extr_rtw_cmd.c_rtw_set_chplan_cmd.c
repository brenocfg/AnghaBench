#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct TYPE_2__ {scalar_t__ ChannelPlan; } ;
struct adapter {TYPE_1__ mlmepriv; struct cmd_priv cmdpriv; } ;
struct SetChannelPlan_param {scalar_t__ channel_plan; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FAIL ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _SetChannelPlan ; 
 int /*<<< orphan*/  _drv_notice_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct SetChannelPlan_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct SetChannelPlan_param*) ; 
 scalar_t__ rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int rtw_hal_is_disable_sw_channel_plan (struct adapter*) ; 
 int /*<<< orphan*/  rtw_is_channel_plan_valid (scalar_t__) ; 
 void* rtw_zmalloc (int) ; 
 scalar_t__ set_chplan_hdl (struct adapter*,unsigned char*) ; 

u8 rtw_set_chplan_cmd(struct adapter *padapter, u8 chplan, u8 enqueue, u8 swconfig)
{
	struct	cmd_obj *pcmdobj;
	struct	SetChannelPlan_param *setChannelPlan_param;
	struct	cmd_priv   *pcmdpriv = &padapter->cmdpriv;

	u8 res = _SUCCESS;

	RT_TRACE(_module_rtl871x_cmd_c_, _drv_notice_, ("+rtw_set_chplan_cmd\n"));

	/*  check if allow software config */
	if (swconfig && rtw_hal_is_disable_sw_channel_plan(padapter) == true) {
		res = _FAIL;
		goto exit;
	}

	/* check input parameter */
	if (!rtw_is_channel_plan_valid(chplan)) {
		res = _FAIL;
		goto exit;
	}

	/* prepare cmd parameter */
	setChannelPlan_param = rtw_zmalloc(sizeof(struct SetChannelPlan_param));
	if (setChannelPlan_param == NULL) {
		res = _FAIL;
		goto exit;
	}
	setChannelPlan_param->channel_plan = chplan;

	if (enqueue) {
		/* need enqueue, prepare cmd_obj and enqueue */
		pcmdobj = rtw_zmalloc(sizeof(struct cmd_obj));
		if (pcmdobj == NULL) {
			kfree(setChannelPlan_param);
			res = _FAIL;
			goto exit;
		}

		init_h2fwcmd_w_parm_no_rsp(pcmdobj, setChannelPlan_param, GEN_CMD_CODE(_SetChannelPlan));
		res = rtw_enqueue_cmd(pcmdpriv, pcmdobj);
	} else {
		/* no need to enqueue, do the cmd hdl directly and free cmd parameter */
		if (H2C_SUCCESS != set_chplan_hdl(padapter, (unsigned char *)setChannelPlan_param))
			res = _FAIL;

		kfree(setChannelPlan_param);
	}

	/* do something based on res... */
	if (res == _SUCCESS)
		padapter->mlmepriv.ChannelPlan = chplan;

exit:
	return res;
}