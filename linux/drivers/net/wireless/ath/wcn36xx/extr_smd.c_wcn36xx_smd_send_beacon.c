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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
struct wcn36xx_hal_send_beacon_req_msg {int beacon_length; int beacon_length6; int* beacon; int* bssid; int tim_ie_offset; int p2p_ie_offset; TYPE_1__ header; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
struct sk_buff {int* data; int len; } ;
struct ieee80211_vif {scalar_t__ type; int* addr; } ;

/* Variables and functions */
 int BEACON_TEMPLATE_SIZE ; 
 int ENOMEM ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_send_beacon_req_msg,int /*<<< orphan*/ ) ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_send_beacon_req_msg) ; 
 int TIM_MIN_PVM_SIZE ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 int /*<<< orphan*/  WCN36XX_HAL_SEND_BEACON_REQ ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  memmove (int*,int*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_send_beacon(struct wcn36xx *wcn, struct ieee80211_vif *vif,
			    struct sk_buff *skb_beacon, u16 tim_off,
			    u16 p2p_off)
{
	struct wcn36xx_hal_send_beacon_req_msg msg_body;
	int ret, pad, pvm_len;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SEND_BEACON_REQ);

	pvm_len = skb_beacon->data[tim_off + 1] - 3;
	pad = TIM_MIN_PVM_SIZE - pvm_len;

	/* Padding is irrelevant to mesh mode since tim_off is always 0. */
	if (vif->type == NL80211_IFTYPE_MESH_POINT)
		pad = 0;

	msg_body.beacon_length = skb_beacon->len + pad;
	/* TODO need to find out why + 6 is needed */
	msg_body.beacon_length6 = msg_body.beacon_length + 6;

	if (msg_body.beacon_length > BEACON_TEMPLATE_SIZE) {
		wcn36xx_err("Beacon is to big: beacon size=%d\n",
			      msg_body.beacon_length);
		ret = -ENOMEM;
		goto out;
	}
	memcpy(msg_body.beacon, skb_beacon->data, skb_beacon->len);
	memcpy(msg_body.bssid, vif->addr, ETH_ALEN);

	if (pad > 0) {
		/*
		 * The wcn36xx FW has a fixed size for the PVM in the TIM. If
		 * given the beacon template from mac80211 with a PVM shorter
		 * than the FW expectes it will overwrite the data after the
		 * TIM.
		 */
		wcn36xx_dbg(WCN36XX_DBG_HAL, "Pad TIM PVM. %d bytes at %d\n",
			    pad, pvm_len);
		memmove(&msg_body.beacon[tim_off + 5 + pvm_len + pad],
			&msg_body.beacon[tim_off + 5 + pvm_len],
			skb_beacon->len - (tim_off + 5 + pvm_len));
		memset(&msg_body.beacon[tim_off + 5 + pvm_len], 0, pad);
		msg_body.beacon[tim_off + 1] += pad;
	}

	/* TODO need to find out why this is needed? */
	if (vif->type == NL80211_IFTYPE_MESH_POINT)
		/* mesh beacon don't need this, so push further down */
		msg_body.tim_ie_offset = 256;
	else
		msg_body.tim_ie_offset = tim_off+4;
	msg_body.p2p_ie_offset = p2p_off;
	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal send beacon beacon_length %d\n",
		    msg_body.beacon_length);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_send_beacon failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_send_beacon response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}