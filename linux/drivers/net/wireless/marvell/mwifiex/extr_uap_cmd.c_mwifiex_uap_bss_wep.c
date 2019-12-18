#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct mwifiex_uap_bss_param {TYPE_2__* wep_cfg; } ;
struct mwifiex_ie_types_header {int dummy; } ;
struct TYPE_3__ {void* len; void* type; } ;
struct host_cmd_tlv_wep_key {int /*<<< orphan*/  key; int /*<<< orphan*/  is_default; int /*<<< orphan*/  key_index; TYPE_1__ header; } ;
struct TYPE_4__ {scalar_t__ length; int /*<<< orphan*/  key; int /*<<< orphan*/  is_default; int /*<<< orphan*/  key_index; } ;

/* Variables and functions */
 int NUM_WEP_KEYS ; 
 scalar_t__ TLV_TYPE_UAP_WEP_KEY ; 
 scalar_t__ WLAN_KEY_LEN_WEP104 ; 
 scalar_t__ WLAN_KEY_LEN_WEP40 ; 
 void* cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mwifiex_uap_bss_wep(u8 **tlv_buf, void *cmd_buf, u16 *param_size)
{
	struct host_cmd_tlv_wep_key *wep_key;
	u16 cmd_size = *param_size;
	int i;
	u8 *tlv = *tlv_buf;
	struct mwifiex_uap_bss_param *bss_cfg = cmd_buf;

	for (i = 0; i < NUM_WEP_KEYS; i++) {
		if (bss_cfg->wep_cfg[i].length &&
		    (bss_cfg->wep_cfg[i].length == WLAN_KEY_LEN_WEP40 ||
		     bss_cfg->wep_cfg[i].length == WLAN_KEY_LEN_WEP104)) {
			wep_key = (struct host_cmd_tlv_wep_key *)tlv;
			wep_key->header.type =
				cpu_to_le16(TLV_TYPE_UAP_WEP_KEY);
			wep_key->header.len =
				cpu_to_le16(bss_cfg->wep_cfg[i].length + 2);
			wep_key->key_index = bss_cfg->wep_cfg[i].key_index;
			wep_key->is_default = bss_cfg->wep_cfg[i].is_default;
			memcpy(wep_key->key, bss_cfg->wep_cfg[i].key,
			       bss_cfg->wep_cfg[i].length);
			cmd_size += sizeof(struct mwifiex_ie_types_header) + 2 +
				    bss_cfg->wep_cfg[i].length;
			tlv += sizeof(struct mwifiex_ie_types_header) + 2 +
				    bss_cfg->wep_cfg[i].length;
		}
	}

	*param_size = cmd_size;
	*tlv_buf = tlv;

	return;
}