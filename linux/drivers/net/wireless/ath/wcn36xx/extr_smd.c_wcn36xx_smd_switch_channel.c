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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_switch_channel_req_msg {int tx_mgmt_power; int max_tx_power; TYPE_1__ header; int /*<<< orphan*/  self_sta_mac_addr; scalar_t__ channel_number; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct ieee80211_vif {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_switch_channel_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_switch_channel_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_HAL_CH_SWITCH_REQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_switch_channel_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_switch_channel(struct wcn36xx *wcn,
			       struct ieee80211_vif *vif, int ch)
{
	struct wcn36xx_hal_switch_channel_req_msg msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_CH_SWITCH_REQ);

	msg_body.channel_number = (u8)ch;
	msg_body.tx_mgmt_power = 0xbf;
	msg_body.max_tx_power = 0xbf;
	memcpy(msg_body.self_sta_mac_addr, vif->addr, ETH_ALEN);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_switch_channel failed\n");
		goto out;
	}
	ret = wcn36xx_smd_switch_channel_rsp(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_switch_channel response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}