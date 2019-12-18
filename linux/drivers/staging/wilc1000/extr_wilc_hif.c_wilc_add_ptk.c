#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
struct wilc_vif {int dummy; } ;
struct wilc_sta_wpa_ptk {int /*<<< orphan*/ * key; scalar_t__ key_len; int /*<<< orphan*/  mac_addr; scalar_t__ index; } ;
struct wilc_ap_wpa_ptk {int /*<<< orphan*/ * key; scalar_t__ key_len; int /*<<< orphan*/  mac_addr; scalar_t__ index; } ;
struct wid {int size; scalar_t__* val; void* type; void* id; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int ARRAY_SIZE (struct wid*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* WID_11I_MODE ; 
 void* WID_ADD_PTK ; 
 void* WID_CHAR ; 
 void* WID_STR ; 
 scalar_t__ WILC_AP_MODE ; 
 scalar_t__ WILC_RX_MIC_KEY_LEN ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 scalar_t__ WILC_STATION_MODE ; 
 scalar_t__ WILC_TX_MIC_KEY_LEN ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,scalar_t__ const*) ; 
 int /*<<< orphan*/  kfree (struct wilc_sta_wpa_ptk*) ; 
 struct wilc_sta_wpa_ptk* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__ const*,scalar_t__) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_add_ptk(struct wilc_vif *vif, const u8 *ptk, u8 ptk_key_len,
		 const u8 *mac_addr, const u8 *rx_mic, const u8 *tx_mic,
		 u8 mode, u8 cipher_mode, u8 index)
{
	int result = 0;
	u8 t_key_len  = ptk_key_len + WILC_RX_MIC_KEY_LEN + WILC_TX_MIC_KEY_LEN;

	if (mode == WILC_AP_MODE) {
		struct wid wid_list[2];
		struct wilc_ap_wpa_ptk *key_buf;

		wid_list[0].id = WID_11I_MODE;
		wid_list[0].type = WID_CHAR;
		wid_list[0].size = sizeof(char);
		wid_list[0].val = (s8 *)&cipher_mode;

		key_buf = kzalloc(sizeof(*key_buf) + t_key_len, GFP_KERNEL);
		if (!key_buf)
			return -ENOMEM;

		ether_addr_copy(key_buf->mac_addr, mac_addr);
		key_buf->index = index;
		key_buf->key_len = t_key_len;
		memcpy(&key_buf->key[0], ptk, ptk_key_len);

		if (rx_mic)
			memcpy(&key_buf->key[ptk_key_len], rx_mic,
			       WILC_RX_MIC_KEY_LEN);

		if (tx_mic)
			memcpy(&key_buf->key[ptk_key_len + WILC_RX_MIC_KEY_LEN],
			       tx_mic, WILC_TX_MIC_KEY_LEN);

		wid_list[1].id = WID_ADD_PTK;
		wid_list[1].type = WID_STR;
		wid_list[1].size = sizeof(*key_buf) + t_key_len;
		wid_list[1].val = (u8 *)key_buf;
		result = wilc_send_config_pkt(vif, WILC_SET_CFG, wid_list,
					      ARRAY_SIZE(wid_list));
		kfree(key_buf);
	} else if (mode == WILC_STATION_MODE) {
		struct wid wid;
		struct wilc_sta_wpa_ptk *key_buf;

		key_buf = kzalloc(sizeof(*key_buf) + t_key_len, GFP_KERNEL);
		if (!key_buf)
			return -ENOMEM;

		ether_addr_copy(key_buf->mac_addr, mac_addr);
		key_buf->key_len = t_key_len;
		memcpy(&key_buf->key[0], ptk, ptk_key_len);

		if (rx_mic)
			memcpy(&key_buf->key[ptk_key_len], rx_mic,
			       WILC_RX_MIC_KEY_LEN);

		if (tx_mic)
			memcpy(&key_buf->key[ptk_key_len + WILC_RX_MIC_KEY_LEN],
			       tx_mic, WILC_TX_MIC_KEY_LEN);

		wid.id = WID_ADD_PTK;
		wid.type = WID_STR;
		wid.size = sizeof(*key_buf) + t_key_len;
		wid.val = (s8 *)key_buf;
		result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
		kfree(key_buf);
	}

	return result;
}