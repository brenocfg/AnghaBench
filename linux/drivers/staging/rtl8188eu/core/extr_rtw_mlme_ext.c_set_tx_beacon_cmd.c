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
struct wlan_bssid_ex {scalar_t__ ie_length; scalar_t__ ies; } ;
struct mlme_ext_info {int /*<<< orphan*/  hidden_ssid_mode; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct cmd_priv cmdpriv; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ _BEACON_IE_OFFSET_ ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _TX_Beacon_CMD_ ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct wlan_bssid_ex*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 struct wlan_bssid_ex* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct cmd_obj* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 int update_hidden_ssid (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

u8 set_tx_beacon_cmd(struct adapter *padapter)
{
	struct cmd_obj *ph2c;
	struct wlan_bssid_ex *ptxBeacon_parm;
	struct cmd_priv *pcmdpriv = &padapter->cmdpriv;
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &pmlmeext->mlmext_info;
	u8 res;
	int len_diff = 0;

	ph2c = kzalloc(sizeof(struct cmd_obj), GFP_ATOMIC);
	if (!ph2c) {
		res = _FAIL;
		goto exit;
	}

	ptxBeacon_parm = kmemdup(&pmlmeinfo->network,
				sizeof(struct wlan_bssid_ex), GFP_ATOMIC);
	if (ptxBeacon_parm == NULL) {
		kfree(ph2c);
		res = _FAIL;
		goto exit;
	}

	len_diff = update_hidden_ssid(ptxBeacon_parm->ies+_BEACON_IE_OFFSET_,
				      ptxBeacon_parm->ie_length-_BEACON_IE_OFFSET_,
				      pmlmeinfo->hidden_ssid_mode);
	ptxBeacon_parm->ie_length += len_diff;

	init_h2fwcmd_w_parm_no_rsp(ph2c, ptxBeacon_parm, _TX_Beacon_CMD_);

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

exit:
	return res;
}