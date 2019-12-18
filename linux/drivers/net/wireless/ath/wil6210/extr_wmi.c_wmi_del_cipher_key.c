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
typedef  int /*<<< orphan*/  u8 ;
struct wmi_delete_cipher_key_cmd {int /*<<< orphan*/  mac; int /*<<< orphan*/  key_index; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_DELETE_CIPHER_KEY_CMDID ; 
 int /*<<< orphan*/  WMI_MAC_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int /*<<< orphan*/ ) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_delete_cipher_key_cmd*,int) ; 

int wmi_del_cipher_key(struct wil6210_vif *vif, u8 key_index,
		       const void *mac_addr, int key_usage)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wmi_delete_cipher_key_cmd cmd = {
		.key_index = key_index,
	};

	if (mac_addr)
		memcpy(cmd.mac, mac_addr, WMI_MAC_LEN);

	return wmi_send(wil, WMI_DELETE_CIPHER_KEY_CMDID, vif->mid,
			&cmd, sizeof(cmd));
}