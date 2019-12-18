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
struct lbs_private {int* wep_key_len; int wep_tx_key; int /*<<< orphan*/ * wep_key; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_set_wep {int /*<<< orphan*/ * keymaterial; int /*<<< orphan*/ * keytype; void* action; void* keyindex; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_SET_WEP ; 
 int CMD_ACT_ADD ; 
 int /*<<< orphan*/  CMD_TYPE_WEP_104_BIT ; 
 int /*<<< orphan*/  CMD_TYPE_WEP_40_BIT ; 
#define  WLAN_KEY_LEN_WEP104 129 
#define  WLAN_KEY_LEN_WEP40 128 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_set_wep*) ; 
 int lbs_remove_wep_keys (struct lbs_private*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_set_wep*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_set_wep_keys(struct lbs_private *priv)
{
	struct cmd_ds_802_11_set_wep cmd;
	int i;
	int ret;

	/*
	 * command         13 00
	 * size            50 00
	 * sequence        xx xx
	 * result          00 00
	 * action          02 00     ACT_ADD
	 * transmit key    00 00
	 * type for key 1  01        WEP40
	 * type for key 2  00
	 * type for key 3  00
	 * type for key 4  00
	 * key 1           39 39 39 39 39 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * key 2           00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * key 3           00 00 00 00 00 00 00 00
	 *                 00 00 00 00 00 00 00 00
	 * key 4           00 00 00 00 00 00 00 00
	 */
	if (priv->wep_key_len[0] || priv->wep_key_len[1] ||
	    priv->wep_key_len[2] || priv->wep_key_len[3]) {
		/* Only set wep keys if we have at least one of them */
		memset(&cmd, 0, sizeof(cmd));
		cmd.hdr.size = cpu_to_le16(sizeof(cmd));
		cmd.keyindex = cpu_to_le16(priv->wep_tx_key);
		cmd.action = cpu_to_le16(CMD_ACT_ADD);

		for (i = 0; i < 4; i++) {
			switch (priv->wep_key_len[i]) {
			case WLAN_KEY_LEN_WEP40:
				cmd.keytype[i] = CMD_TYPE_WEP_40_BIT;
				break;
			case WLAN_KEY_LEN_WEP104:
				cmd.keytype[i] = CMD_TYPE_WEP_104_BIT;
				break;
			default:
				cmd.keytype[i] = 0;
				break;
			}
			memcpy(cmd.keymaterial[i], priv->wep_key[i],
			       priv->wep_key_len[i]);
		}

		ret = lbs_cmd_with_response(priv, CMD_802_11_SET_WEP, &cmd);
	} else {
		/* Otherwise remove all wep keys */
		ret = lbs_remove_wep_keys(priv);
	}

	return ret;
}