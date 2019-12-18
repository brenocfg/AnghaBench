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
typedef  int /*<<< orphan*/  u8 ;
struct wlan_bssid_ex {int dummy; } ;
struct mlme_ext_info {int /*<<< orphan*/  hidden_ssid_mode; int /*<<< orphan*/  network; } ;
struct mlme_ext_priv {struct mlme_ext_info mlmext_info; } ;
struct cmd_priv {int dummy; } ;
struct cmd_obj {int dummy; } ;
struct adapter {struct mlme_ext_priv mlmeextpriv; struct cmd_priv cmdpriv; } ;
struct TYPE_2__ {scalar_t__ IELength; scalar_t__ IEs; } ;
struct Tx_Beacon_param {TYPE_1__ network; } ;

/* Variables and functions */
 int /*<<< orphan*/  GEN_CMD_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ _BEACON_IE_OFFSET_ ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _TX_Beacon ; 
 int /*<<< orphan*/  init_h2fwcmd_w_parm_no_rsp (struct cmd_obj*,struct Tx_Beacon_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cmd_obj*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_enqueue_cmd (struct cmd_priv*,struct cmd_obj*) ; 
 void* rtw_zmalloc (int) ; 
 int update_hidden_ssid (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

u8 set_tx_beacon_cmd(struct adapter *padapter)
{
	struct cmd_obj	*ph2c;
	struct Tx_Beacon_param	*ptxBeacon_parm;
	struct cmd_priv *pcmdpriv = &(padapter->cmdpriv);
	struct mlme_ext_priv *pmlmeext = &padapter->mlmeextpriv;
	struct mlme_ext_info *pmlmeinfo = &(pmlmeext->mlmext_info);
	u8 res = _SUCCESS;
	int len_diff = 0;

	ph2c = rtw_zmalloc(sizeof(struct cmd_obj));
	if (ph2c == NULL) {
		res = _FAIL;
		goto exit;
	}

	ptxBeacon_parm = rtw_zmalloc(sizeof(struct Tx_Beacon_param));
	if (ptxBeacon_parm == NULL) {
		kfree(ph2c);
		res = _FAIL;
		goto exit;
	}

	memcpy(&(ptxBeacon_parm->network), &(pmlmeinfo->network), sizeof(struct wlan_bssid_ex));

	len_diff = update_hidden_ssid(
		ptxBeacon_parm->network.IEs+_BEACON_IE_OFFSET_
		, ptxBeacon_parm->network.IELength-_BEACON_IE_OFFSET_
		, pmlmeinfo->hidden_ssid_mode
	);
	ptxBeacon_parm->network.IELength += len_diff;

	init_h2fwcmd_w_parm_no_rsp(ph2c, ptxBeacon_parm, GEN_CMD_CODE(_TX_Beacon));

	res = rtw_enqueue_cmd(pcmdpriv, ph2c);

exit:
	return res;
}