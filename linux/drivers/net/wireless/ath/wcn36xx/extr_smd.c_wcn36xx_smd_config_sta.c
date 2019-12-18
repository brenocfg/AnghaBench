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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_config_sta_params {int /*<<< orphan*/  aid; int /*<<< orphan*/  mac; int /*<<< orphan*/  type; int /*<<< orphan*/  bssid; int /*<<< orphan*/  bssid_index; int /*<<< orphan*/  sta_index; int /*<<< orphan*/  action; } ;
struct wcn36xx_hal_config_sta_req_msg {TYPE_1__ header; struct wcn36xx_hal_config_sta_params sta_params; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_sta {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_config_sta_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_config_sta_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  WCN36XX_HAL_CONFIG_STA_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int /*<<< orphan*/  wcn36xx_is_fw_version (struct wcn36xx*,int,int,int,int) ; 
 int wcn36xx_smd_config_sta_rsp (struct wcn36xx*,struct ieee80211_sta*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_config_sta_v1 (struct wcn36xx*,struct wcn36xx_hal_config_sta_req_msg*) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_smd_set_sta_params (struct wcn36xx*,struct ieee80211_vif*,struct ieee80211_sta*,struct wcn36xx_hal_config_sta_params*) ; 

int wcn36xx_smd_config_sta(struct wcn36xx *wcn, struct ieee80211_vif *vif,
			   struct ieee80211_sta *sta)
{
	struct wcn36xx_hal_config_sta_req_msg msg;
	struct wcn36xx_hal_config_sta_params *sta_params;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg, WCN36XX_HAL_CONFIG_STA_REQ);

	sta_params = &msg.sta_params;

	wcn36xx_smd_set_sta_params(wcn, vif, sta, sta_params);

	if (!wcn36xx_is_fw_version(wcn, 1, 2, 2, 24)) {
		ret = wcn36xx_smd_config_sta_v1(wcn, &msg);
	} else {
		PREPARE_HAL_BUF(wcn->hal_buf, msg);

		wcn36xx_dbg(WCN36XX_DBG_HAL,
			    "hal config sta action %d sta_index %d bssid_index %d bssid %pM type %d mac %pM aid %d\n",
			    sta_params->action, sta_params->sta_index,
			    sta_params->bssid_index, sta_params->bssid,
			    sta_params->type, sta_params->mac, sta_params->aid);

		ret = wcn36xx_smd_send_and_wait(wcn, msg.header.len);
	}
	if (ret) {
		wcn36xx_err("Sending hal_config_sta failed\n");
		goto out;
	}
	ret = wcn36xx_smd_config_sta_rsp(wcn,
					 sta,
					 wcn->hal_buf,
					 wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_config_sta response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}