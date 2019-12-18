#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u8 ;
struct TYPE_6__ {int /*<<< orphan*/  len; } ;
struct TYPE_5__ {int enc_type; int single_tid_rc; TYPE_1__* key; scalar_t__ wep_type; void* def_wep_idx; void* sta_index; } ;
struct wcn36xx_hal_set_sta_key_req_msg {TYPE_3__ header; TYPE_2__ set_sta_key_params; } ;
struct wcn36xx {int /*<<< orphan*/  hal_mutex; int /*<<< orphan*/  hal_rsp_len; int /*<<< orphan*/  hal_buf; } ;
typedef  enum ani_ed_type { ____Placeholder_ani_ed_type } ani_ed_type ;
struct TYPE_4__ {int unicast; int /*<<< orphan*/  key; void* length; scalar_t__ pae_role; int /*<<< orphan*/  direction; void* id; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_HAL_MSG (struct wcn36xx_hal_set_sta_key_req_msg,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREPARE_HAL_BUF (int /*<<< orphan*/ ,struct wcn36xx_hal_set_sta_key_req_msg) ; 
 int WCN36XX_HAL_ED_WEP104 ; 
 int WCN36XX_HAL_ED_WEP40 ; 
 int /*<<< orphan*/  WCN36XX_HAL_SET_STAKEY_REQ ; 
 int /*<<< orphan*/  WCN36XX_HAL_TX_RX ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,void*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,...) ; 
 int wcn36xx_smd_rsp_status_check (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int wcn36xx_smd_send_and_wait (struct wcn36xx*,int /*<<< orphan*/ ) ; 

int wcn36xx_smd_set_stakey(struct wcn36xx *wcn,
			   enum ani_ed_type enc_type,
			   u8 keyidx,
			   u8 keylen,
			   u8 *key,
			   u8 sta_index)
{
	struct wcn36xx_hal_set_sta_key_req_msg msg_body;
	int ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SET_STAKEY_REQ);

	msg_body.set_sta_key_params.sta_index = sta_index;
	msg_body.set_sta_key_params.enc_type = enc_type;

	if (enc_type == WCN36XX_HAL_ED_WEP104 ||
	    enc_type == WCN36XX_HAL_ED_WEP40) {
		/* Use bss key for wep (static) */
		msg_body.set_sta_key_params.def_wep_idx = keyidx;
		msg_body.set_sta_key_params.wep_type = 0;
	} else {
		msg_body.set_sta_key_params.key[0].id = keyidx;
		msg_body.set_sta_key_params.key[0].unicast = 1;
		msg_body.set_sta_key_params.key[0].direction = WCN36XX_HAL_TX_RX;
		msg_body.set_sta_key_params.key[0].pae_role = 0;
		msg_body.set_sta_key_params.key[0].length = keylen;
		memcpy(msg_body.set_sta_key_params.key[0].key, key, keylen);
	}

	msg_body.set_sta_key_params.single_tid_rc = 1;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_wait(wcn, msg_body.header.len);
	if (ret) {
		wcn36xx_err("Sending hal_set_stakey failed\n");
		goto out;
	}
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	if (ret) {
		wcn36xx_err("hal_set_stakey response failed err=%d\n", ret);
		goto out;
	}
out:
	mutex_unlock(&wcn->hal_mutex);
	return ret;
}