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
struct wcn36xx_hal_send_probe_resp_req_msg {TYPE_1__ header; int /*<<< orphan*/ * bssid; int /*<<< orphan*/  probe_resp_template_len; int /*<<< orphan*/  probe_resp_template; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEACON_TEMPLATE_SIZE ; 
 int E2BIG ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_send_probe_resp_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_send_probe_resp_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  WCN36XX_HAL_UPDATE_PROBE_RSP_TEMPLATE_REQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_update_proberesp_tmpl(struct wcn36xx *wcn,
				      struct ieee80211_vif *vif,
				      struct sk_buff *skb)
{
	struct wcn36xx_hal_send_probe_resp_req_msg msg;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg, WCN36XX_HAL_UPDATE_PROBE_RSP_TEMPLATE_REQ);

	if (skb->len > BEACON_TEMPLATE_SIZE) {
		wcn36xx_warn("probe response template is too big: %d\n",
			     skb->len);
		ret = -E2BIG;
		goto out;
	}

	msg.probe_resp_template_len = skb->len;
	memcpy(&msg.probe_resp_template, skb->data, skb->len);

	memcpy(msg.bssid, vif->addr, ETH_ALEN);

	PREPARE_HAL_BUF(wcn->hal_buf, msg);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal update probe rsp len %d bssid %pM\n",
		    msg.probe_resp_template_len, msg.bssid);

	ret = wcn36xx_smd_send_and_wait(wcn, msg.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_update_proberesp_tmpl failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_update_proberesp_tmpl response failed err=%d\n",
			    ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}