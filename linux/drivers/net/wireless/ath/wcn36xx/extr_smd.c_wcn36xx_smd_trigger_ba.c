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
struct TYPE_2__ {int len; } ;
struct wcn36xx_hal_trigger_ba_req_msg {int candidate_cnt; TYPE_1__ header; scalar_t__ session_id; } ;
struct wcn36xx_hal_trigger_ba_req_candidate {int tid_bitmap; int /*<<< orphan*/  sta_index; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; scalar_t__ hal_buf; } ;
typedef  int /*<<< orphan*/  msg_body ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_trigger_ba_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (scalar_t__,struct wcn36xx_hal_trigger_ba_req_msg) ; 
 int /*<<< orphan*/  WCN36XX_HAL_TRIGGER_BA_REQ ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int) ; 
 int wcn36xx_smd_trigger_ba_rsp (scalar_t__,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_trigger_ba(struct wcn36xx *wcn, u8 sta_index)
{
	struct wcn36xx_hal_trigger_ba_req_msg msg_body;
	struct wcn36xx_hal_trigger_ba_req_candidate *candidate;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_TRIGGER_BA_REQ);

	msg_body.session_id = 0;
	msg_body.candidate_cnt = 1;
	msg_body.header.len += sizeof(*candidate);
	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	candidate = (struct wcn36xx_hal_trigger_ba_req_candidate *)
		(wcn->hal_buf + sizeof(msg_body));
	candidate->sta_index = sta_index;
	candidate->tid_bitmap = 1;

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_trigger_ba failed\n");
		goto out;
	}
	ret = wcn36xx_smd_trigger_ba_rsp(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_trigger_ba response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}