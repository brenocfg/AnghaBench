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
typedef  int /*<<< orphan*/  u32 ;
struct wilc_vif {TYPE_1__* hif_drv; } ;
struct wilc_gtk_key {int key_len; int /*<<< orphan*/ * key; scalar_t__ index; int /*<<< orphan*/ * rsc; int /*<<< orphan*/ * mac_addr; } ;
struct wid {int size; scalar_t__* val; void* type; void* id; } ;
typedef  scalar_t__ s8 ;
struct TYPE_2__ {scalar_t__ hif_state; scalar_t__ const* assoc_bssid; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct wid*) ; 
 int ENOMEM ; 
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HOST_IF_CONNECTED ; 
 void* WID_11I_MODE ; 
 void* WID_ADD_RX_GTK ; 
 void* WID_CHAR ; 
 void* WID_STR ; 
 scalar_t__ WILC_AP_MODE ; 
 scalar_t__ WILC_RX_MIC_KEY_LEN ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 scalar_t__ WILC_STATION_MODE ; 
 scalar_t__ WILC_TX_MIC_KEY_LEN ; 
 int /*<<< orphan*/  kfree (struct wilc_gtk_key*) ; 
 struct wilc_gtk_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__ const*,scalar_t__) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_add_rx_gtk(struct wilc_vif *vif, const u8 *rx_gtk, u8 gtk_key_len,
		    u8 index, u32 key_rsc_len, const u8 *key_rsc,
		    const u8 *rx_mic, const u8 *tx_mic, u8 mode,
		    u8 cipher_mode)
{
	int result = 0;
	struct wilc_gtk_key *gtk_key;
	int t_key_len = gtk_key_len + WILC_RX_MIC_KEY_LEN + WILC_TX_MIC_KEY_LEN;

	gtk_key = kzalloc(sizeof(*gtk_key) + t_key_len, GFP_KERNEL);
	if (!gtk_key)
		return -ENOMEM;

	/* fill bssid value only in station mode */
	if (mode == WILC_STATION_MODE &&
	    vif->hif_drv->hif_state == HOST_IF_CONNECTED)
		memcpy(gtk_key->mac_addr, vif->hif_drv->assoc_bssid, ETH_ALEN);

	if (key_rsc)
		memcpy(gtk_key->rsc, key_rsc, 8);
	gtk_key->index = index;
	gtk_key->key_len = t_key_len;
	memcpy(&gtk_key->key[0], rx_gtk, gtk_key_len);

	if (rx_mic)
		memcpy(&gtk_key->key[gtk_key_len], rx_mic, WILC_RX_MIC_KEY_LEN);

	if (tx_mic)
		memcpy(&gtk_key->key[gtk_key_len + WILC_RX_MIC_KEY_LEN],
		       tx_mic, WILC_TX_MIC_KEY_LEN);

	if (mode == WILC_AP_MODE) {
		struct wid wid_list[2];

		wid_list[0].id = WID_11I_MODE;
		wid_list[0].type = WID_CHAR;
		wid_list[0].size = sizeof(char);
		wid_list[0].val = (s8 *)&cipher_mode;

		wid_list[1].id = WID_ADD_RX_GTK;
		wid_list[1].type = WID_STR;
		wid_list[1].size = sizeof(*gtk_key) + t_key_len;
		wid_list[1].val = (u8 *)gtk_key;

		result = wilc_send_config_pkt(vif, WILC_SET_CFG, wid_list,
					      ARRAY_SIZE(wid_list));
	} else if (mode == WILC_STATION_MODE) {
		struct wid wid;

		wid.id = WID_ADD_RX_GTK;
		wid.type = WID_STR;
		wid.size = sizeof(*gtk_key) + t_key_len;
		wid.val = (u8 *)gtk_key;
		result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	}

	kfree(gtk_key);
	return result;
}