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
typedef  int u8 ;
struct wilc_wep_key {int index; int key_len; int /*<<< orphan*/  key; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {int size; int* val; void* type; int /*<<< orphan*/  id; } ;
typedef  int s8 ;
typedef  enum authtype { ____Placeholder_authtype } authtype ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct wid*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WID_11I_MODE ; 
 int /*<<< orphan*/  WID_AUTH_TYPE ; 
 void* WID_CHAR ; 
 void* WID_STR ; 
 int /*<<< orphan*/  WID_WEP_KEY_VALUE ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  kfree (struct wilc_wep_key*) ; 
 struct wilc_wep_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int /*<<< orphan*/ ) ; 

int wilc_add_wep_key_bss_ap(struct wilc_vif *vif, const u8 *key, u8 len,
			    u8 index, u8 mode, enum authtype auth_type)
{
	struct wid wid_list[3];
	int result;
	struct wilc_wep_key *wep_key;

	wid_list[0].id = WID_11I_MODE;
	wid_list[0].type = WID_CHAR;
	wid_list[0].size = sizeof(char);
	wid_list[0].val = &mode;

	wid_list[1].id = WID_AUTH_TYPE;
	wid_list[1].type = WID_CHAR;
	wid_list[1].size = sizeof(char);
	wid_list[1].val = (s8 *)&auth_type;

	wid_list[2].id = WID_WEP_KEY_VALUE;
	wid_list[2].type = WID_STR;
	wid_list[2].size = sizeof(*wep_key) + len;
	wep_key = kzalloc(wid_list[2].size, GFP_KERNEL);
	if (!wep_key)
		return -ENOMEM;

	wid_list[2].val = (u8 *)wep_key;

	wep_key->index = index;
	wep_key->key_len = len;
	memcpy(wep_key->key, key, len);
	result = wilc_send_config_pkt(vif, WILC_SET_CFG, wid_list,
				      ARRAY_SIZE(wid_list));
	if (result)
		netdev_err(vif->ndev,
			   "Failed to add wep ap key config packet\n");

	kfree(wep_key);
	return result;
}