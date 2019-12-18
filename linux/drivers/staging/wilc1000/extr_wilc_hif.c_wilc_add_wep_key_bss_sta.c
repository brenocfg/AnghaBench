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
typedef  void* u8 ;
struct wilc_wep_key {int /*<<< orphan*/  key; void* key_len; void* index; } ;
struct wilc_vif {int /*<<< orphan*/  ndev; } ;
struct wid {void** val; void* size; int /*<<< orphan*/  type; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WID_ADD_WEP_KEY ; 
 int /*<<< orphan*/  WID_STR ; 
 int /*<<< orphan*/  WILC_SET_CFG ; 
 int /*<<< orphan*/  kfree (struct wilc_wep_key*) ; 
 struct wilc_wep_key* kzalloc (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void* const*,void*) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int wilc_send_config_pkt (struct wilc_vif*,int /*<<< orphan*/ ,struct wid*,int) ; 

int wilc_add_wep_key_bss_sta(struct wilc_vif *vif, const u8 *key, u8 len,
			     u8 index)
{
	struct wid wid;
	int result;
	struct wilc_wep_key *wep_key;

	wid.id = WID_ADD_WEP_KEY;
	wid.type = WID_STR;
	wid.size = sizeof(*wep_key) + len;
	wep_key = kzalloc(wid.size, GFP_KERNEL);
	if (!wep_key)
		return -ENOMEM;

	wid.val = (u8 *)wep_key;

	wep_key->index = index;
	wep_key->key_len = len;
	memcpy(wep_key->key, key, len);

	result = wilc_send_config_pkt(vif, WILC_SET_CFG, &wid, 1);
	if (result)
		netdev_err(vif->ndev,
			   "Failed to add wep key config packet\n");

	kfree(wep_key);
	return result;
}