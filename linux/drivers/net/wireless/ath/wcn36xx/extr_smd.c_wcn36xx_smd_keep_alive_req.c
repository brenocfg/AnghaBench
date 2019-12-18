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
struct wcn36xx_vif {int /*<<< orphan*/  bss_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_keep_alive_req_msg {int packet_type; TYPE_1__ header; int /*<<< orphan*/  time_period; int /*<<< orphan*/  bss_index; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_keep_alive_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_keep_alive_req_msg) ; 
 int WCN36XX_HAL_KEEP_ALIVE_NULL_PKT ; 
 int /*<<< orphan*/  WCN36XX_HAL_KEEP_ALIVE_REQ ; 
 int WCN36XX_HAL_KEEP_ALIVE_UNSOLICIT_ARP_RSP ; 
 int /*<<< orphan*/  WCN36XX_KEEP_ALIVE_TIME_PERIOD ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*,int) ; 

int wcn36xx_smd_keep_alive_req(struct wcn36xx *wcn,
			       struct ieee80211_vif *vif,
			       int packet_type)
{
	struct wcn36xx_hal_keep_alive_req_msg msg_body;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_KEEP_ALIVE_REQ);

	if (packet_type == WCN36XX_HAL_KEEP_ALIVE_NULL_PKT) {
		msg_body.bss_index = vif_priv->bss_index;
		msg_body.packet_type = WCN36XX_HAL_KEEP_ALIVE_NULL_PKT;
		msg_body.time_period = WCN36XX_KEEP_ALIVE_TIME_PERIOD;
	} else if (packet_type == WCN36XX_HAL_KEEP_ALIVE_UNSOLICIT_ARP_RSP) {
		/* TODO: it also support ARP response type */
	} else {
		wcn36xx_warn("unknown keep alive packet type %d\n", packet_type);
		ret = -EINVAL;
		goto out;
	}

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_keep_alive failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_keep_alive response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}