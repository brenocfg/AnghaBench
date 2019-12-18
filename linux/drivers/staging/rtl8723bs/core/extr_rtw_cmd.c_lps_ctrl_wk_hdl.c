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
struct pwrctrl_priv {int /*<<< orphan*/  DelayLPSLastTimeStamp; int /*<<< orphan*/  LpsIdleCount; } ;
struct mlme_priv {int dummy; } ;
struct adapter {struct mlme_priv mlmepriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_H2C_FW_JOINBSSRPT ; 
#define  LPS_CTRL_CONNECT 134 
#define  LPS_CTRL_DISCONNECT 133 
#define  LPS_CTRL_JOINBSS 132 
#define  LPS_CTRL_LEAVE 131 
#define  LPS_CTRL_SCAN 130 
#define  LPS_CTRL_SPECIAL_PACKET 129 
#define  LPS_CTRL_TRAFFIC_BUSY 128 
 int /*<<< orphan*/  LPS_Leave (struct adapter*,char*) ; 
 int /*<<< orphan*/  PACKET_DHCP ; 
 int /*<<< orphan*/  WIFI_ADHOC_MASTER_STATE ; 
 int /*<<< orphan*/  WIFI_ADHOC_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 struct pwrctrl_priv* adapter_to_pwrctl (struct adapter*) ; 
 int check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hal_btcoex_ScanNotify (struct adapter*,int) ; 
 int /*<<< orphan*/  hal_btcoex_SpecialPacketNotify (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  rtw_btcoex_MediaStatusNotify (struct adapter*,int) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 

void lps_ctrl_wk_hdl(struct adapter *padapter, u8 lps_ctrl_type)
{
	struct pwrctrl_priv *pwrpriv = adapter_to_pwrctl(padapter);
	struct mlme_priv *pmlmepriv = &(padapter->mlmepriv);
	u8 mstatus;

	if ((check_fwstate(pmlmepriv, WIFI_ADHOC_MASTER_STATE) == true)
		|| (check_fwstate(pmlmepriv, WIFI_ADHOC_STATE) == true)) {
		return;
	}

	switch (lps_ctrl_type) {
	case LPS_CTRL_SCAN:
		/* DBG_871X("LPS_CTRL_SCAN\n"); */
		hal_btcoex_ScanNotify(padapter, true);

		if (check_fwstate(pmlmepriv, _FW_LINKED) == true) {
			/*  connect */
			LPS_Leave(padapter, "LPS_CTRL_SCAN");
		}
		break;
	case LPS_CTRL_JOINBSS:
		/* DBG_871X("LPS_CTRL_JOINBSS\n"); */
		LPS_Leave(padapter, "LPS_CTRL_JOINBSS");
		break;
	case LPS_CTRL_CONNECT:
		/* DBG_871X("LPS_CTRL_CONNECT\n"); */
		mstatus = 1;/* connect */
		/*  Reset LPS Setting */
		pwrpriv->LpsIdleCount = 0;
		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_JOINBSSRPT, (u8 *)(&mstatus));
		rtw_btcoex_MediaStatusNotify(padapter, mstatus);
		break;
	case LPS_CTRL_DISCONNECT:
		/* DBG_871X("LPS_CTRL_DISCONNECT\n"); */
		mstatus = 0;/* disconnect */
		rtw_btcoex_MediaStatusNotify(padapter, mstatus);
		LPS_Leave(padapter, "LPS_CTRL_DISCONNECT");
		rtw_hal_set_hwreg(padapter, HW_VAR_H2C_FW_JOINBSSRPT, (u8 *)(&mstatus));
		break;
	case LPS_CTRL_SPECIAL_PACKET:
		/* DBG_871X("LPS_CTRL_SPECIAL_PACKET\n"); */
		pwrpriv->DelayLPSLastTimeStamp = jiffies;
		hal_btcoex_SpecialPacketNotify(padapter, PACKET_DHCP);
		LPS_Leave(padapter, "LPS_CTRL_SPECIAL_PACKET");
		break;
	case LPS_CTRL_LEAVE:
		/* DBG_871X("LPS_CTRL_LEAVE\n"); */
		LPS_Leave(padapter, "LPS_CTRL_LEAVE");
		break;
	case LPS_CTRL_TRAFFIC_BUSY:
		LPS_Leave(padapter, "LPS_CTRL_TRAFFIC_BUSY");
	default:
		break;
	}
}