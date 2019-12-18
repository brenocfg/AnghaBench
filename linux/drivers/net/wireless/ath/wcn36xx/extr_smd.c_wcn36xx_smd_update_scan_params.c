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
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_update_scan_params_req_ex {int dot11d_enabled; int dot11d_resolved; size_t channel_count; int active_min_ch_time; int active_max_ch_time; int passive_min_ch_time; int passive_max_ch_time; TYPE_1__ header; int /*<<< orphan*/  state; int /*<<< orphan*/  channels; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_update_scan_params_req_ex,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PHY_SINGLE_CHANNEL_CENTERED ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_update_scan_params_req_ex) ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  WCN36XX_HAL_UPDATE_SCAN_PARAM_REQ ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_update_scan_params_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_update_scan_params(struct wcn36xx *wcn,
				   u8 *channels, size_t channel_count)
{
	struct wcn36xx_hal_update_scan_params_req_ex msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_UPDATE_SCAN_PARAM_REQ);

	msg_body.dot11d_enabled	= false;
	msg_body.dot11d_resolved = true;

	msg_body.channel_count = channel_count;
	memcpy(msg_body.channels, channels, channel_count);
	msg_body.active_min_ch_time = 60;
	msg_body.active_max_ch_time = 120;
	msg_body.passive_min_ch_time = 60;
	msg_body.passive_max_ch_time = 110;
	msg_body.state = PHY_SINGLE_CHANNEL_CENTERED;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal update scan params channel_count %d\n",
		    msg_body.channel_count);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_update_scan_params failed\n");
		goto out;
	}
	ret = wcn36xx_smd_update_scan_params_rsp(wcn->hal_buf,
						 wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_update_scan_params response failed err=%d\n",
			    ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}