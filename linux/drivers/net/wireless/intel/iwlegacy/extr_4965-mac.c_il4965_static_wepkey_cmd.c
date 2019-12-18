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
typedef  scalar_t__ u8 ;
struct il_wep_key {int dummy; } ;
struct il_wep_cmd {int num_keys; int /*<<< orphan*/  global_key_type; TYPE_1__* key; } ;
struct TYPE_6__ {TYPE_2__* wep_keys; } ;
struct il_priv {TYPE_3__ _4965; } ;
struct il_host_cmd {size_t len; int /*<<< orphan*/  flags; struct il_wep_cmd* data; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  key; scalar_t__ key_size; } ;
struct TYPE_4__ {int key_idx; int key_offset; int /*<<< orphan*/ * key; scalar_t__ key_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SYNC ; 
 int /*<<< orphan*/  C_WEPKEY ; 
 int WEP_INVALID_OFFSET ; 
 int WEP_KEYS_MAX ; 
 int /*<<< orphan*/  WEP_KEY_WEP_TYPE ; 
 int il_send_cmd (struct il_priv*,struct il_host_cmd*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (struct il_wep_cmd*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  might_sleep () ; 

__attribute__((used)) static int
il4965_static_wepkey_cmd(struct il_priv *il, bool send_if_empty)
{
	int i;
	u8 buff[sizeof(struct il_wep_cmd) +
		sizeof(struct il_wep_key) * WEP_KEYS_MAX];
	struct il_wep_cmd *wep_cmd = (struct il_wep_cmd *)buff;
	size_t cmd_size = sizeof(struct il_wep_cmd);
	struct il_host_cmd cmd = {
		.id = C_WEPKEY,
		.data = wep_cmd,
		.flags = CMD_SYNC,
	};
	bool not_empty = false;

	might_sleep();

	memset(wep_cmd, 0,
	       cmd_size + (sizeof(struct il_wep_key) * WEP_KEYS_MAX));

	for (i = 0; i < WEP_KEYS_MAX; i++) {
		u8 key_size = il->_4965.wep_keys[i].key_size;

		wep_cmd->key[i].key_idx = i;
		if (key_size) {
			wep_cmd->key[i].key_offset = i;
			not_empty = true;
		} else
			wep_cmd->key[i].key_offset = WEP_INVALID_OFFSET;

		wep_cmd->key[i].key_size = key_size;
		memcpy(&wep_cmd->key[i].key[3], il->_4965.wep_keys[i].key, key_size);
	}

	wep_cmd->global_key_type = WEP_KEY_WEP_TYPE;
	wep_cmd->num_keys = WEP_KEYS_MAX;

	cmd_size += sizeof(struct il_wep_key) * WEP_KEYS_MAX;
	cmd.len = cmd_size;

	if (not_empty || send_if_empty)
		return il_send_cmd(il, &cmd);
	else
		return 0;
}