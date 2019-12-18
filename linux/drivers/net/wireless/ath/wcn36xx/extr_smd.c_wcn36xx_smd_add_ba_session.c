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
typedef  void* u8 ;
typedef  void* u16 ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_add_ba_session_req_msg {int dialog_token; int policy; TYPE_1__ header; void* direction; void* ssn; scalar_t__ timeout; int /*<<< orphan*/  buffer_size; void* tid; int /*<<< orphan*/  mac_addr; void* sta_index; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct ieee80211_sta {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_add_ba_session_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_add_ba_session_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_AGGR_BUFFER_SIZE ; 
 int /*<<< orphan*/  WCN36XX_HAL_ADD_BA_SESSION_REQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_add_ba_session(struct wcn36xx *wcn,
		struct ieee80211_sta *sta,
		u16 tid,
		u16 *ssn,
		u8 direction,
		u8 sta_index)
{
	struct wcn36xx_hal_add_ba_session_req_msg msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_ADD_BA_SESSION_REQ);

	msg_body.sta_index = sta_index;
	memcpy(&msg_body.mac_addr, sta->addr, ETH_ALEN);
	msg_body.dialog_token = 0x10;
	msg_body.tid = tid;

	/* Immediate BA because Delayed BA is not supported */
	msg_body.policy = 1;
	msg_body.buffer_size = WCN36XX_AGGR_BUFFER_SIZE;
	msg_body.timeout = 0;
	if (ssn)
		msg_body.ssn = *ssn;
	msg_body.direction = direction;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_add_ba_session failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_add_ba_session response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}